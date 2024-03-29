#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include <functional>
#include <iostream>
#include <exception>
#include <algorithm>
#include <sstream>
#include <variant>
#include <optional>

#include "dwislpy-ast.hh"
#include "dwislpy-util.hh"
#include "dwislpy-check.hh"

//
// dwislpy-ast.cc
//
// Below are the implementations of methods for AST nodes. They are organized
// into groups. The first group represents the DWISLPY interpreter by giving
// the code for
//
//    Prgm::run, Blck::exec, Stmt::exec, Expn::eval
//
// The second group AST::output and AST::dump performs pretty printing
// of SLPY code and also the output of the AST, resp.
//

//
// to_string
//
// Helper function that converts a DwiSlpy value into a string.
// This is meant to be used by `print` and also `str`.
//
std::string to_string(Valu v) {
    if (std::holds_alternative<int>(v)) {
        return std::to_string(std::get<int>(v));
    } else if (std::holds_alternative<std::string>(v)) {
        return std::get<std::string>(v);
    } else if (std::holds_alternative<bool>(v)) {
        if (std::get<bool>(v)) {
            return "True";
        } else {
            return "False";
        }
    } else if (std::holds_alternative<none>(v)) {
        return "None";
    } else {
        return "<unknown>";
    }
}

//
// to_repr
//
// Helper function that converts a DwiSlpy value into a string.
// This is meant to mimic Python's `repr` function in that it gives
// the source code string for the value. Used by routines that dump
// a literal value.
//
std::string to_repr(Valu v) {
    if (std::holds_alternative<std::string>(v)) {
        //
        // Strings have to be converted to show their quotes and also
        // to have the unprintable chatacters given as \escape sequences.
        //
        return "\"" + re_escape(std::get<std::string>(v)) + "\"";
    } else {
        //
        // The other types aren't special. (This will have to change when
        // we have value types that aren't "ground" types e.g. list types.)
        //
        return to_string(v);
    }
}



// * * * * *
// The DWISLPY interpreter
//

//
// Prgm::run, Blck::exec, Stmt::exec
//
//  - execute DWISLPY statements, changing the runtime context mapping
//    variables to their current values.
//

void Prgm::run(void) const {
    Ctxt main_ctxt { };
    main->exec(defs,main_ctxt);
}

std::optional<Valu> Defn::call(const Defs& defs,
                               const Expn_vec& args,
                               const Ctxt& ctxt) {
    Ctxt locals {};
    int i=0;
    for (Expn_ptr expn : args) {
        std::string local = formal(i)->name;
        i++;
        Valu value = expn->eval(defs,ctxt);
        locals[local] = value;
    }
    return body->exec(defs, locals);
}

std::optional<Valu> Blck::exec(const Defs& defs, Ctxt& ctxt) const {
    for (Stmt_ptr s : stmts) {
        std::optional<Valu> rv = s->exec(defs,ctxt);
        if (rv.has_value()) {
            return rv;
        }
    }
    return std::nullopt;
}

std::optional<Valu> Asgn::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    ctxt[name] = expn->eval(defs,ctxt);
    return std::nullopt;
}

std::optional<Valu> Ntro::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    ctxt[name] = expn->eval(defs,ctxt);
    return std::nullopt;
}

std::optional<Valu> Pass::exec([[maybe_unused]] const Defs& defs,
                               [[maybe_unused]] Ctxt& ctxt) const {
    // does nothing!
    return std::nullopt;
}

std::optional<Valu> Pseq::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    if (ctxt.count(name) > 0) {
      Valu lv = expn->eval(defs,ctxt);
      Valu rv = ctxt.at(name);
      Valu savers;
      if (std::holds_alternative<int>(lv)
          && std::holds_alternative<int>(rv)) {
          int ln = std::get<int>(lv);
          int rn = std::get<int>(rv);
           savers = {ln + rn};
      } else if (std::holds_alternative<std::string>(lv)
                 && std::holds_alternative<std::string>(rv)) {
          std::string ls = std::get<std::string>(lv);
          std::string rs = std::get<std::string>(rv);
          savers =  {ls + rs};
      } else {
          std::string msg = "Run-time error: wrong operand type for plus.";
          throw DwislpyError { where(), msg };
      }
      ctxt[name] = savers;
    } else {
      std::string msg = "Run-time error: variable '" + name +"'";
      msg += "not defined.";
      throw DwislpyError { where(), msg };
    }
    return std::nullopt;
}

std::optional<Valu> Mseq::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    if (ctxt.count(name) > 0) {
      Valu lv = expn->eval(defs,ctxt);
      Valu rv = ctxt.at(name);
      Valu savers;
      if (std::holds_alternative<int>(lv)
          && std::holds_alternative<int>(rv)) {
          int ln = std::get<int>(lv);
          int rn = std::get<int>(rv);
           savers = {ln - rn};
      } else {
          std::string msg = "Run-time error: wrong operand type for Minus.";
          throw DwislpyError { where(), msg };
      }
      ctxt[name] = savers;
    } else {
      std::string msg = "Run-time error: variable '" + name +"'";
      msg += "not defined.";
      throw DwislpyError { where(), msg };
    }
    return std::nullopt;
}


std::optional<Valu> Prnt::exec(const Defs& defs, Ctxt& ctxt) const {
    std::cout << to_string(expn->eval(defs,ctxt)) << std::endl;
    return std::nullopt;
}

std::optional<Valu> PCll::exec(const Defs& defs, Ctxt& ctxt) const {
    if (defs.count(name) == 0) {
        std::string msg = "Run-time error: procedure '" + name +"'";
        msg += " is not defined.";
        throw DwislpyError { where(), msg };
    }
    Defn_ptr defn = defs.at(name);
    if (defn->arity() != params.size()) {
        std::string msg = "Run-time error: wrong number of arguments to ";
        msg += "procedure '" + name +"'.";
        throw DwislpyError { where(), msg };
    }
    defn->call(defs,params,ctxt);
    return std::nullopt;
}

std::optional<Valu> PRtn::exec([[maybe_unused]] const Defs& defs,
                               [[maybe_unused]] Ctxt& ctxt) const {
    return std::optional<Valu> { Valu { None } };
}

std::optional<Valu> FRtn::exec(const Defs& defs, Ctxt& ctxt) const {
    return std::optional<Valu> { expn->eval(defs, ctxt) };
}

std::optional<Valu> IfEl::exec(const Defs& defs, Ctxt& ctxt) const {
    Valu cond = cndn->eval(defs,ctxt);
    if (!std::holds_alternative<bool>(cond)) {
        std::string msg = "Run-time error: condition not a boolean.";
        throw DwislpyError { where(), msg };
    }
    if (std::get<bool>(cond)) {
        return then_blck->exec(defs,ctxt);
    } else {
        return else_blck->exec(defs,ctxt);
    }
}

std::optional<Valu> Whle::exec(const Defs& defs, Ctxt& ctxt) const {
    Valu cond = cndn->eval(defs,ctxt);
    while (std::holds_alternative<bool>(cond) && std::get<bool>(cond)) {
        std::optional<Valu> maybe_return = blck->exec(defs,ctxt);
        if (maybe_return.has_value()) {
            return maybe_return;
        }
        cond = cndn->eval(defs,ctxt);
    }
    if (!std::holds_alternative<bool>(cond)) {
        std::string msg = "Run-time error: condition not a boolean.";
        throw DwislpyError { where(), msg };
    }
    return std::nullopt;
}

//
// Expn::eval
//
//  - evaluate DWISLPY expressions within a runtime context to determine their
//    (integer) value.
//

Valu Plus::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln + rn};
    } else if (std::holds_alternative<std::string>(lv)
               && std::holds_alternative<std::string>(rv)) {
        std::string ls = std::get<std::string>(lv);
        std::string rs = std::get<std::string>(rv);
        return Valu {ls + rs};
    } else {
        std::string msg = "Run-time error: wrong operand type for plus.";
        throw DwislpyError { where(), msg };
    }
}

Valu Mnus::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln - rn};
    } else {
        std::string msg = "Run-time error: wrong operand type for minus.";
        throw DwislpyError { where(), msg };
    }
}

Valu Tmes::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln * rn};
    } else {
        // Exercise: make this work for (int,str) and (str,int).
        std::string msg = "Run-time error: wrong operand type for times.";
        throw DwislpyError { where(), msg };
    }
}

Valu IDiv::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        if (rn == 0) {
            throw DwislpyError { where(), "Run-time error: division by 0."};
        } else {
            return Valu {ln / rn};
        }
    } else {
        std::string msg = "Run-time error: wrong operand type for quotient.";
        throw DwislpyError { where(), msg };
    }
}

Valu IMod::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        if (rn == 0) {
            throw DwislpyError { where(), "Run-time error: division by 0."};
        } else {
            return Valu {ln % rn};
        }
    } else {
        std::string msg = "Run-time error: wrong operand type for remainder.";
        throw DwislpyError { where(), msg };
    }
}

Valu Less::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln < rn};
    } else if (std::holds_alternative<std::string>(lv)
               && std::holds_alternative<std::string>(rv)) {
        std::string ls = std::get<std::string>(lv);
        std::string rs = std::get<std::string>(rv);
        return Valu {ls < rs};
    } else if (std::holds_alternative<bool>(lv)
               && std::holds_alternative<bool>(rv)) {
        bool lb = std::get<bool>(lv);
        bool rb = std::get<bool>(rv);
        return Valu {!lb && rb};
    } else {
        std::string msg = "Run-time error: wrong operand type for comparison.";
        throw DwislpyError { where(), msg };
    }
}

Valu Equl::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln == rn};
    } else if (std::holds_alternative<std::string>(lv)
               && std::holds_alternative<std::string>(rv)) {
        std::string ls = std::get<std::string>(lv);
        std::string rs = std::get<std::string>(rv);
        return Valu {ls == rs};
    } else if (std::holds_alternative<bool>(lv)
               && std::holds_alternative<bool>(rv)) {
        bool lb = std::get<bool>(lv);
        bool rb = std::get<bool>(rv);
        return Valu {lb == rb};
    } else if (std::holds_alternative<none>(lv)
               && std::holds_alternative<none>(rv)) {
        return Valu {true};
    } else {
        return Valu {false};
    }
}

Valu LsEq::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln <= rn};
    } else if (std::holds_alternative<std::string>(lv)
               && std::holds_alternative<std::string>(rv)) {
        std::string ls = std::get<std::string>(lv);
        std::string rs = std::get<std::string>(rv);
        return Valu {ls <= rs};
    } else if (std::holds_alternative<bool>(lv)
               && std::holds_alternative<bool>(rv)) {
        bool lb = std::get<bool>(lv);
        bool rb = std::get<bool>(rv);
        return Valu {!lb || rb};
    } else {
        std::string msg = "Run-time error: wrong operand type for comparison.";
        throw DwislpyError { where(), msg };
    }
}

Valu And::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    if (std::holds_alternative<bool>(lv)) {
        bool lb = std::get<bool>(lv);
        if (lb) {
            return rght->eval(defs,ctxt);
        } else {
            return lv;
        }
    } else {
        std::string msg = "Run-time error: wrong operand type for conjunction.";
        throw DwislpyError { where(), msg };
    }
}

Valu Or::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    if (std::holds_alternative<bool>(lv)) {
        bool lb = std::get<bool>(lv);
        if (lb) {
            return lv;
        } else {
            return rght->eval(defs,ctxt);
        }
    } else {
        std::string msg = "Run-time error: wrong operand type for disjunction.";
        throw DwislpyError { where(), msg };
    }
}

Valu Not::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu ev = expn->eval(defs,ctxt);
    if (std::holds_alternative<bool>(ev)) {
        bool eb = std::get<bool>(ev);
        return Valu { !eb };
    } else {
        std::string msg = "Run-time error: wrong operand type for logical negation.";
        throw DwislpyError { where(), msg };
    }
}

Valu Ltrl::eval([[maybe_unused]] const Defs& defs,
                [[maybe_unused]] const Ctxt& ctxt) const {
    return valu;
}

Valu Lkup::eval([[maybe_unused]] const Defs& defs, const Ctxt& ctxt) const {
    if (ctxt.count(name) > 0) {
        return ctxt.at(name);
    } else {
        std::string msg = "Run-time error: variable '" + name +"'";
        msg += "not defined.";
        throw DwislpyError { where(), msg };
    }
}

Valu Inpt::eval([[maybe_unused]] const Defs& defs, const Ctxt& ctxt) const {
    Valu v = expn->eval(defs,ctxt);
    if (std::holds_alternative<std::string>(v)) {
        //
        std::string prompt = std::get<std::string>(v);
        std::cout << prompt;
        //
        std::string vl;
        std::cin >> vl;
        //
        return Valu {vl};
    } else {
        std::string msg = "Run-time error: prompt is not a string.";
        throw DwislpyError { where(), msg };
    }
}

Valu IntC::eval([[maybe_unused]] const Defs& defs, const Ctxt& ctxt) const {
    Valu v = expn->eval(defs,ctxt);
    if (std::holds_alternative<int>(v)) {
        return Valu {v};
    } else if (std::holds_alternative<std::string>(v)) {
        std::string s = std::get<std::string>(v);
        try {
            int i = std::stoi(s);
            return Valu {i};
        } catch (std::invalid_argument e) {
            std::string msg = "Run-time error: \""+s+"\"";
            msg += "cannot be converted to an int.";
            throw DwislpyError { where(), msg };
        }
    } else if (std::holds_alternative<bool>(v)) {
        bool b = std::get<bool>(v);
        return Valu {b ? 1 : 0};
    } else {
        std::string msg = "Run-time error: cannot convert to an int.";
        throw DwislpyError { where(), msg };
    }
}

Valu StrC::eval([[maybe_unused]] const Defs& defs, const Ctxt& ctxt) const {
    //
    // The integer conversion operation does nothing in this
    // version of DWISLPY.
    //
    Valu v = expn->eval(defs,ctxt);
    return Valu { to_string(v) };
}

Valu FCll::eval(const Defs& defs, const Ctxt& ctxt) const {
    if (defs.count(name) == 0) {
        std::string msg = "Run-time error: function '" + name +"'";
        msg += " is not defined.";
        throw DwislpyError { where(), msg };
    }
    Defn_ptr defn = defs.at(name);
    if (defn->arity() != params.size()) {
        std::string msg = "Run-time error: wrong number of arguments to ";
        msg += "function '" + name +"'.";
        throw DwislpyError { where(), msg };
    }
    std::optional<Valu> result = defn->call(defs,params,ctxt);
    if (!result.has_value()) {
        std::string msg = "Run-time error: no value returned from ";
        msg += "function '" + name +"'.";
        throw DwislpyError { where(), msg };
    }
    return result.value();
}

// * * * * *
//
// AST::output
//
// - Pretty printer for DWISLPY code represented in an AST.
//
// The code below is an implementation of a pretty printer. For each case
// of an AST node (each subclass) the `output` method provides the means for
// printing the code of the DWISLPY construct it represents.
//
//

void Prgm::output(std::ostream& os) const {
    for (std::pair<Name,Defn_ptr> dfpr : defs) {
        dfpr.second->output(os);
    }
    main->output(os);
}

void Defn::output(std::ostream& os) const {
    os << "def " << name << "(";
    bool comma = false;
    for (unsigned int i=0; i < arity(); i++) {
        if (comma) {
            os << ",";
        }
        SymInfo_ptr frml = formal(i);
        os << frml->name << ":" << type_name(frml->type);
    }
    os << "):" << std::endl;
    body->output(os,"    ");
}


void Blck::output(std::ostream& os, std::string indent) const {
    for (Stmt_ptr s : stmts) {
        s->output(os,indent);
    }
}

void Blck::output(std::ostream& os) const {
    for (Stmt_ptr s : stmts) {
        s->output(os);
    }
}

void Stmt::output(std::ostream& os) const {
    output(os,"");
}

void Asgn::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << name << " = ";
    expn->output(os);
    os << std::endl;
}

void Pseq::output(std::ostream& os, std::string indent) const {
  indent = "";
  os << "(";
  os << name;
  os << " += ";
  expn->output(os);
  os << ")";
    os << std::endl;
}

void Mseq::output(std::ostream& os, std::string indent) const {
  indent = "";
  os << "(";
  os << name;
  os << " -= ";
  expn->output(os);
  os << ")";
    os << std::endl;
}

void Ntro::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << name << " : " << type_name(type) << " = ";
    expn->output(os);
    os << std::endl;
}

void Pass::output(std::ostream& os, std::string indent) const {
    os << indent << "pass" << std::endl;
}

void Prnt::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "print";
    os << "(";
    expn->output(os);
    os << ")";
    os << std::endl;
}

void Whle::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "while ";
    cndn->output(os);
    os << ":";
    os << std::endl;
    blck->output(os,indent + "    ");
}

void IfEl::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "if ";
    cndn->output(os);
    os << ":";
    os << std::endl;
    then_blck->output(os,indent + "    ");
    os << "else:";
    os << std::endl;
    else_blck->output(os,indent + "    ");
}

void PRtn::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "return";
    os << std::endl;
}

void FRtn::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "return ";
    expn->output(os);
    os << std::endl;
}

void PCll::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << name << "(";
    bool comma = false;
    for (Expn_ptr expn : params) {
        if (comma) {
            os << ",";
        }
        expn->output(os);
        comma = true;
    }
    os << ")";
    os << std::endl;
}


void Plus::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " + ";
    rght->output(os);
    os << ")";
}

void Mnus::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " - ";
    rght->output(os);
    os << ")";
}

void Tmes::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " * ";
    rght->output(os);
    os << ")";
}

void IDiv::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " // ";
    rght->output(os);
    os << ")";
}

void IMod::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " % ";
    rght->output(os);
    os << ")";
}

void Less::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " < ";
    rght->output(os);
    os << ")";
}

void LsEq::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " <= ";
    rght->output(os);
    os << ")";
}

void Equl::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " == ";
    rght->output(os);
    os << ")";
}

void And::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " and ";
    rght->output(os);
    os << ")";
}

void Or::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " or ";
    rght->output(os);
    os << ")";
}

void Not::output(std::ostream& os) const {
    os << "(not ";
    expn->output(os);
    os << ")";
}

void Ltrl::output(std::ostream& os) const {
    os << to_repr(valu);
}

void Lkup::output(std::ostream& os) const {
    os << name;
}

void Inpt::output(std::ostream& os) const {
    os << "input(";
    expn->output(os);
    os << ")";
}

void IntC::output(std::ostream& os) const {
    os << "int(";
    expn->output(os);
    os << ")";
}

void StrC::output(std::ostream& os) const {
    os << "str(";
    expn->output(os);
    os << ")";
}

void FCll::output(std::ostream& os) const {
    os << name << "(";
    bool comma = false;
    for (Expn_ptr expn : params) {
        if (comma) {
            os << ",";
        }
        expn->output(os);
        comma = true;
    }
    os << ")";
}


// * * * * *
//
// AST::dump
//
// - Dumps the AST of DWISLPY code.
//
// The code below dumps the contents of an AST as a series of lines
// indented and headed by the AST node type and its subcontents.
//

void dump_indent(int level) {
    //std::string indent { level, std::string {"    "} };
    for (int i=0; i<level; i++) {
        std::cout << "    ";
    }
}

void Prgm::dump(int level) const {
    dump_indent(level);
    std::cout << "PRGM" << std::endl;
    for (std::pair<Name,Defn_ptr> dfpr : defs) {
        dfpr.second->dump(level+1);
    }
    main->dump(level+1);
}

void Defn::dump(int level) const {
    dump_indent(level);
    std::cout << "DEFN" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    for (unsigned int i=0; i < arity(); i++) {
        dump_indent(level+1);
        SymInfo_ptr frml = formal(i);
        std::cout << frml->name << ":" << type_name(frml->type) << std::endl;
    }
    body->dump(level+1);
}

void Blck::dump(int level) const {
    dump_indent(level);
    std::cout << "BLCK" << std::endl;
    for (Stmt_ptr stmt : stmts) {
        stmt->dump(level+1);
    }
}

void Ntro::dump(int level) const {
    dump_indent(level);
    std::cout << "NTRO" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    dump_indent(level+1);
    std::cout << type_name(type) << std::endl;
    expn->dump(level+1);
}

void Asgn::dump(int level) const {
    dump_indent(level);
    std::cout << "ASGN" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    expn->dump(level+1);
}

void Prnt::dump(int level) const {
    dump_indent(level);
    std::cout << "PRNT" << std::endl;
    expn->dump(level+1);
}
void Pseq::dump(int level) const {
    dump_indent(level);
    std::cout << "PSEQ" << std::endl;
    expn->dump(level+1);
}

void Mseq::dump(int level) const {
    dump_indent(level);
    std::cout << "MSEQ" << std::endl;
    expn->dump(level+1);
}

void PRtn::dump(int level) const {
    dump_indent(level);
    std::cout << "PRTN" << std::endl;
}

void FRtn::dump(int level) const {
    dump_indent(level);
    std::cout << "FRTN" << std::endl;
    expn->dump(level+1);
}

void PCll::dump(int level) const {
    dump_indent(level);
    std::cout << "PCLL" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    for (Expn_ptr expn : params) {
         expn->dump(level+1);
    }
}

void Pass::dump(int level) const {
    dump_indent(level);
    std::cout << "PASS" << std::endl;
}

void IfEl::dump(int level) const {
    dump_indent(level);
    std::cout << "IFEL" << std::endl;
    cndn->dump(level+1);
    then_blck->dump(level+1);
    else_blck->dump(level+1);
}

void Whle::dump(int level) const {
    dump_indent(level);
    std::cout << "WHLE" << std::endl;
    cndn->dump(level+1);
    blck->dump(level+1);
}

void Plus::dump(int level) const {
    dump_indent(level);
    std::cout << "PLUS" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Mnus::dump(int level) const {
    dump_indent(level);
    std::cout << "MNUS" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Tmes::dump(int level) const {
    dump_indent(level);
    std::cout << "TMES" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void IDiv::dump(int level) const {
    dump_indent(level);
    std::cout << "IDIV" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void IMod::dump(int level) const {
    dump_indent(level);
    std::cout << "IDIV" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Equl::dump(int level) const {
    dump_indent(level);
    std::cout << "EQUL" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void LsEq::dump(int level) const {
    dump_indent(level);
    std::cout << "LSEQ" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Less::dump(int level) const {
    dump_indent(level);
    std::cout << "Less" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void And::dump(int level) const {
    dump_indent(level);
    std::cout << "AND " << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Or::dump(int level) const {
    dump_indent(level);
    std::cout << "OR  " << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Not::dump(int level) const {
    dump_indent(level);
    std::cout << "NOT " << std::endl;
    expn->dump(level+1);
}

void Ltrl::dump(int level) const {
    dump_indent(level);
    std::cout << "LTRL" << std::endl;
    dump_indent(level+1);
    std::cout << to_repr(valu) << std::endl;
}

void Lkup::dump(int level) const {
    dump_indent(level);
    std::cout << "LKUP" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
}

void Inpt::dump(int level) const {
    dump_indent(level);
    std::cout << "INPT" << std::endl;
    expn->dump(level+1);
}

void IntC::dump(int level) const {
    dump_indent(level);
    std::cout << "INTC" << std::endl;
    expn->dump(level+1);
}

void StrC::dump(int level) const {
    dump_indent(level);
    std::cout << "STRC" << std::endl;
    expn->dump(level+1);
}

void FCll::dump(int level) const {
    dump_indent(level);
    std::cout << "FCLL" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    for (Expn_ptr expn : params) {
         expn->dump(level+1);
    }
}

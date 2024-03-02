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
#include <math.h>

#include "slpy-ast.hh"
#include "slpy-util.hh"

//
// slpy-ast.cc
//
// Below are the implementations of methods of AST nodes. They are organized
// into groups. The first group represents the SLPY interpreter using
//
//    Prgm::run, Blck::exec, Stmt::exec, Expn::eval
//
// The second group AST::output performs pretty printing of SLP code.
//

// * * * * *
// The SLPY interpreter
//

//
// Prgm::run, Blck::exec, Stmt:: exec
//
//  - execute SLPY statements, changing the runtime context mapping
//    variables to their current values.
//

void Prgm::run(void) const {
    Ctxt main_ctxt { };
    main->exec(main_ctxt);
}

void Blck::exec(Ctxt& ctxt) const {
    for (Stmt_ptr s : stmts) {
        s->exec(ctxt);
    }
}

void Asgn::exec(Ctxt& ctxt) const {
    ctxt[name] = expn->eval(ctxt);
}

void Pass::exec(Ctxt& ctxt) const {
    // does nothing!
}

void Prnt::exec(Ctxt& ctxt) const {
    std::cout << expn->eval(ctxt) << std::endl;
}

//
// Expn::eval
//
//  - evaluate SLPY expressions within a runtime context to determine their
//    (integer) value.
//

int Plus::eval(const Ctxt& ctxt) const {
    int lv = left->eval(ctxt);
    int rv = rght->eval(ctxt);
    return (lv + rv);
}

int Mnus::eval(const Ctxt& ctxt) const {
    int lv = left->eval(ctxt);
    int rv = rght->eval(ctxt);
    return (lv - rv);
}

int Tmes::eval(const Ctxt& ctxt) const {
    int lv = left->eval(ctxt);
    int rv = rght->eval(ctxt);
    return (lv * rv);
}

int IDiv::eval(const Ctxt& ctxt) const {
    int lv = left->eval(ctxt);
    int rv = rght->eval(ctxt);
    if (rv == 0) {
        throw SlpyError { where(), "Run-time error: division by 0."};
    } else {
        return (lv / rv);
    }
}
int Powr::eval(const Ctxt& ctxt) const {
    int lv = left->eval(ctxt);
    int rv = rght->eval(ctxt);
    return pow(rv, lv);
}



int IMod::eval(const Ctxt& ctxt) const {
    int lv = left->eval(ctxt);
    int rv = rght->eval(ctxt);
    if (rv == 0) {
        throw SlpyError { where(), "Run-time error: division by 0."};
    } else {
        return (lv % rv);
    }
}

int Nmbr::eval(const Ctxt& ctxt) const {
    return valu;
}

int Lkup::eval(const Ctxt& ctxt) const {
    if (ctxt.count(name) > 0) {
        return ctxt.at(name);
    } else {
        throw SlpyError { where(), "Run-time error: variable '" + name +"' not defined."};
    }
}

int Inpt::eval(const Ctxt& ctxt) const {
    int vl;
    std::cout << prpt;
    std::cin >> vl;
    return vl;
}

int IntC::eval(const Ctxt& ctxt) const {
    //
    // The integer conversion operation does nothing in this
    // version of SLPY.
    //
    return expn->eval(ctxt);
}


// * * * * *
//
// AST::output
//
// - Pretty printer for SLPY code represented in an AST.
//
// The code below is an implementation of a pretty printer. For each case
// of an AST node (each subclass) the `output` method provides the means for
// printing the code of the SLPY construct it represents.
//
//
std::string spaces ="";
void indenter(){
  std::cout << spaces;
}

void Prgm::output(std::ostream& os) const {
  std::cout << "Prgm" << '\n';
    main->output(os);
}

void Blck::output(std::ostream& os, std::string indent) const {
    indent.append("   ");
    for (Stmt_ptr s : stmts) {
        std::cout << indent << '\n';
        s->output(os,indent);
    }
}

void Blck::output(std::ostream& os) const {
    spaces.append("   ");
    indenter();
    std::cout << "Blck" << '\n';
    for (Stmt_ptr s : stmts) {
        s->output(os,"");
    }
    spaces = spaces.substr(0,(spaces.length()-3));
}

void Stmt::output(std::ostream& os) const {
    output(os,"lkjljs");
}

void Asgn::output(std::ostream& os, std::string indent) const {
    spaces.append("   ");
    indenter();
    os << "Asgn" << std::endl;
    spaces.append("   ");
    indenter();
    os << name << '\n';
    indenter();
    expn->output(os);
    spaces = spaces.substr(0,(spaces.length()-6));
    os << std::endl;
}

void Pass::output(std::ostream& os, std::string indent) const {
    os << indent << "pass" << std::endl;
}

void Prnt::output(std::ostream& os, std::string indent) const {
    spaces.append("   ");
    indenter();
    os << "print" << '\n';
    spaces.append("   ");
    indenter();
    expn->output(os);
    os << std::endl;
    spaces = spaces.substr(0,(spaces.length()-3));
}

void Plus::output(std::ostream& os) const {
    os << "Plus" <<'\n';
    spaces.append("   ");
    indenter();
    left->output(os);
    rght->output(os);
    spaces = spaces.substr(0,(spaces.length()-3));
}

void Mnus::output(std::ostream& os) const {
  os << "Minus" <<'\n';
  spaces.append("   ");
  indenter();
  left->output(os);
  rght->output(os);
  spaces = spaces.substr(0,(spaces.length()-3));
}

void Tmes::output(std::ostream& os) const {
    os << "Times" << '\n';
    spaces.append("   ");
    indenter();
    left->output(os);
    rght->output(os);
    spaces = spaces.substr(0,(spaces.length()-3));
}

void IDiv::output(std::ostream& os) const {
    os << "IDiv" << '\n';
    spaces.append("   ");
    indenter();
    left->output(os);
    rght->output(os);
    spaces = spaces.substr(0,(spaces.length()-3));
}
void Powr::output(std::ostream& os) const {
    os << "Powr" << '\n';
    spaces.append("   ");
    indenter();
    rght->output(os);
    left->output(os);
    spaces = spaces.substr(0,(spaces.length()-3));
}


void IMod::output(std::ostream& os) const {
    os << "Mod"<<'\n';
    spaces.append("   ");
    indenter();
    left->output(os);
    rght->output(os);
    spaces = spaces.substr(0,(spaces.length()-3));
}

void Nmbr::output(std::ostream& os) const {
  spaces.append("   ");
  indenter();
    os << "Nbr"<< '\n';
    spaces.append("   ");
    indenter();
    os << std::to_string(valu) << '\n';
      spaces = spaces.substr(0,(spaces.length()-6));
}

void Lkup::output(std::ostream& os) const {
  std::cout << "Lkup" << '\n';
  spaces.append("   ");
  indenter();
  std::cout << name << '\n';
  spaces = spaces.substr(0,(spaces.length()-3));
}

void Inpt::output(std::ostream& os) const {
    spaces.append("   ");
    os << "input" << '\n'<< spaces <<re_escape(prpt) <<'\n';
    spaces = spaces.substr(0,(spaces.length()-3));
}

void IntC::output(std::ostream& os) const {
    os << "int" << '\n';
    spaces.append("   ");
    indenter();
    expn->output(os);
    spaces = spaces.substr(0,(spaces.length()-3));
}

// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "dwislpy-bison.tab.hh"


// Unqualified %code blocks.
#line 25 "dwislpy-bison.yy"


    #include <sstream>
    #include "dwislpy-util.hh"
    #include "dwislpy-main.hh"

    #undef yylex
    #define yylex lexer.yylex


#line 56 "dwislpy-bison.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "dwislpy-bison.yy"
namespace DWISLPY {
#line 148 "dwislpy-bison.tab.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Lexer  &lexer_yyarg, Driver &main_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg),
      main (main_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
    {
      case 44: // nest
      case 45: // blck
        value.move< Blck_ptr > (std::move (that.value));
        break;

      case 48: // expn
        value.move< Expn_ptr > (std::move (that.value));
        break;

      case 43: // prgm
        value.move< Prgm_ptr > (std::move (that.value));
        break;

      case 47: // stmt
        value.move< Stmt_ptr > (std::move (that.value));
        break;

      case 46: // stms
        value.move< Stmt_vec > (std::move (that.value));
        break;

      case 38: // NMBR
        value.move< int > (std::move (that.value));
        break;

      case 39: // NAME
      case 40: // STRG
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
    {
      case 44: // nest
      case 45: // blck
        value.copy< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 48: // expn
        value.copy< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 43: // prgm
        value.copy< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 47: // stmt
        value.copy< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 46: // stms
        value.copy< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 38: // NMBR
        value.copy< int > (YY_MOVE (that.value));
        break;

      case 39: // NAME
      case 40: // STRG
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 44: // nest
      case 45: // blck
        value.move< Blck_ptr > (YY_MOVE (s.value));
        break;

      case 48: // expn
        value.move< Expn_ptr > (YY_MOVE (s.value));
        break;

      case 43: // prgm
        value.move< Prgm_ptr > (YY_MOVE (s.value));
        break;

      case 47: // stmt
        value.move< Stmt_ptr > (YY_MOVE (s.value));
        break;

      case 46: // stms
        value.move< Stmt_vec > (YY_MOVE (s.value));
        break;

      case 38: // NMBR
        value.move< int > (YY_MOVE (s.value));
        break;

      case 39: // NAME
      case 40: // STRG
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  Parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  Parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 44: // nest
      case 45: // blck
        value.YY_MOVE_OR_COPY< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 48: // expn
        value.YY_MOVE_OR_COPY< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 43: // prgm
        value.YY_MOVE_OR_COPY< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 47: // stmt
        value.YY_MOVE_OR_COPY< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 46: // stms
        value.YY_MOVE_OR_COPY< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 38: // NMBR
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 39: // NAME
      case 40: // STRG
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 44: // nest
      case 45: // blck
        value.move< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 48: // expn
        value.move< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 43: // prgm
        value.move< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 47: // stmt
        value.move< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 46: // stms
        value.move< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 38: // NMBR
        value.move< int > (YY_MOVE (that.value));
        break;

      case 39: // NAME
      case 40: // STRG
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 44: // nest
      case 45: // blck
        value.copy< Blck_ptr > (that.value);
        break;

      case 48: // expn
        value.copy< Expn_ptr > (that.value);
        break;

      case 43: // prgm
        value.copy< Prgm_ptr > (that.value);
        break;

      case 47: // stmt
        value.copy< Stmt_ptr > (that.value);
        break;

      case 46: // stms
        value.copy< Stmt_vec > (that.value);
        break;

      case 38: // NMBR
        value.copy< int > (that.value);
        break;

      case 39: // NAME
      case 40: // STRG
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 44: // nest
      case 45: // blck
        value.move< Blck_ptr > (that.value);
        break;

      case 48: // expn
        value.move< Expn_ptr > (that.value);
        break;

      case 43: // prgm
        value.move< Prgm_ptr > (that.value);
        break;

      case 47: // stmt
        value.move< Stmt_ptr > (that.value);
        break;

      case 46: // stms
        value.move< Stmt_vec > (that.value);
        break;

      case 38: // NMBR
        value.move< int > (that.value);
        break;

      case 39: // NAME
      case 40: // STRG
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 44: // nest
      case 45: // blck
        yylhs.value.emplace< Blck_ptr > ();
        break;

      case 48: // expn
        yylhs.value.emplace< Expn_ptr > ();
        break;

      case 43: // prgm
        yylhs.value.emplace< Prgm_ptr > ();
        break;

      case 47: // stmt
        yylhs.value.emplace< Stmt_ptr > ();
        break;

      case 46: // stms
        yylhs.value.emplace< Stmt_vec > ();
        break;

      case 38: // NMBR
        yylhs.value.emplace< int > ();
        break;

      case 39: // NAME
      case 40: // STRG
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 100 "dwislpy-bison.yy"
       {
      main.set(yystack_[0].value.as < Prgm_ptr > ());
  }
#line 910 "dwislpy-bison.tab.cc"
    break;

  case 3:
#line 106 "dwislpy-bison.yy"
       {
      Defs ds { };
      Blck_ptr b = yystack_[0].value.as < Blck_ptr > ();
      yylhs.value.as < Prgm_ptr > () = Prgm_ptr { new Prgm {ds, b, b->where()} };
  }
#line 920 "dwislpy-bison.tab.cc"
    break;

  case 4:
#line 135 "dwislpy-bison.yy"
                 {
    yylhs.value.as < Blck_ptr > () = yystack_[1].value.as < Blck_ptr > ();
  }
#line 928 "dwislpy-bison.tab.cc"
    break;

  case 5:
#line 141 "dwislpy-bison.yy"
       {
      Stmt_vec ss = yystack_[0].value.as < Stmt_vec > ();
      yylhs.value.as < Blck_ptr > () = Blck_ptr { new Blck {ss, ss[0]->where()} };
  }
#line 937 "dwislpy-bison.tab.cc"
    break;

  case 6:
#line 148 "dwislpy-bison.yy"
            {
      Stmt_vec ss = yystack_[1].value.as < Stmt_vec > ();
      ss.push_back(yystack_[0].value.as < Stmt_ptr > ());
      yylhs.value.as < Stmt_vec > () = ss;
  }
#line 947 "dwislpy-bison.tab.cc"
    break;

  case 7:
#line 153 "dwislpy-bison.yy"
       {
      Stmt_vec ss { };
      ss.push_back(yystack_[0].value.as < Stmt_ptr > ());
      yylhs.value.as < Stmt_vec > () = ss;
  }
#line 957 "dwislpy-bison.tab.cc"
    break;

  case 8:
#line 161 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Stmt_ptr > () = Asgn_ptr { new Asgn {yystack_[3].value.as < std::string > (),yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[2].location)} };
  }
#line 965 "dwislpy-bison.tab.cc"
    break;

  case 9:
#line 164 "dwislpy-bison.yy"
                      {
    yylhs.value.as < Stmt_ptr > () = Pseq_ptr { new Pseq {yystack_[3].value.as < std::string > (),yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[2].location)} };
  }
#line 973 "dwislpy-bison.tab.cc"
    break;

  case 10:
#line 167 "dwislpy-bison.yy"
                           {
    yylhs.value.as < Stmt_ptr > () = IfEl_ptr { new IfEl {yystack_[3].value.as < Expn_ptr > (),yystack_[0].value.as < Blck_ptr > (),lexer.locate(yystack_[3].location)} };
}
#line 981 "dwislpy-bison.tab.cc"
    break;

  case 11:
#line 170 "dwislpy-bison.yy"
                           {
    yylhs.value.as < Stmt_ptr > () = Whle_ptr { new Whle {yystack_[3].value.as < Expn_ptr > (),yystack_[0].value.as < Blck_ptr > (),lexer.locate(yystack_[3].location)} };
}
#line 989 "dwislpy-bison.tab.cc"
    break;

  case 12:
#line 173 "dwislpy-bison.yy"
                      {
    yylhs.value.as < Stmt_ptr > () = Mseq_ptr { new Mseq {yystack_[3].value.as < std::string > (),yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[2].location)} };
  }
#line 997 "dwislpy-bison.tab.cc"
    break;

  case 13:
#line 176 "dwislpy-bison.yy"
            {
      yylhs.value.as < Stmt_ptr > () = Pass_ptr { new Pass {lexer.locate(yystack_[1].location)} };
  }
#line 1005 "dwislpy-bison.tab.cc"
    break;

  case 14:
#line 179 "dwislpy-bison.yy"
                           {
      yylhs.value.as < Stmt_ptr > () = Prnt_ptr { new Prnt {yystack_[2].value.as < Expn_ptr > (),lexer.locate(yystack_[4].location)} };
  }
#line 1013 "dwislpy-bison.tab.cc"
    break;

  case 15:
#line 185 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Plus_ptr { new Plus {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1021 "dwislpy-bison.tab.cc"
    break;

  case 16:
#line 188 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Mnus_ptr { new Mnus {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1029 "dwislpy-bison.tab.cc"
    break;

  case 17:
#line 191 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = And_ptr { new And {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1037 "dwislpy-bison.tab.cc"
    break;

  case 18:
#line 194 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Less_ptr { new Less {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1045 "dwislpy-bison.tab.cc"
    break;

  case 19:
#line 197 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = LsEq_ptr { new LsEq {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1053 "dwislpy-bison.tab.cc"
    break;

  case 20:
#line 200 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Equl_ptr { new Equl {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1061 "dwislpy-bison.tab.cc"
    break;

  case 21:
#line 203 "dwislpy-bison.yy"
            {
      yylhs.value.as < Expn_ptr > () = Not_ptr { new Not {yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
    }
#line 1069 "dwislpy-bison.tab.cc"
    break;

  case 22:
#line 206 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Oorr_ptr { new Oorr {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1077 "dwislpy-bison.tab.cc"
    break;

  case 23:
#line 209 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Tmes_ptr { new Tmes {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1085 "dwislpy-bison.tab.cc"
    break;

  case 24:
#line 212 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = IDiv_ptr { new IDiv {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1093 "dwislpy-bison.tab.cc"
    break;

  case 25:
#line 215 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = IMod_ptr { new IMod {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1101 "dwislpy-bison.tab.cc"
    break;

  case 26:
#line 218 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {yystack_[0].value.as < int > ()},lexer.locate(yystack_[0].location)} };
  }
#line 1109 "dwislpy-bison.tab.cc"
    break;

  case 27:
#line 221 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {de_escape(yystack_[0].value.as < std::string > ())},lexer.locate(yystack_[0].location)} };
  }
#line 1117 "dwislpy-bison.tab.cc"
    break;

  case 28:
#line 224 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {true},lexer.locate(yystack_[0].location)} };
  }
#line 1125 "dwislpy-bison.tab.cc"
    break;

  case 29:
#line 227 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {false},lexer.locate(yystack_[0].location)} };
  }
#line 1133 "dwislpy-bison.tab.cc"
    break;

  case 30:
#line 230 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {None},lexer.locate(yystack_[0].location)} };
  }
#line 1141 "dwislpy-bison.tab.cc"
    break;

  case 31:
#line 233 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Expn_ptr > () = Inpt_ptr { new Inpt {yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[3].location)} };
  }
#line 1149 "dwislpy-bison.tab.cc"
    break;

  case 32:
#line 236 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Expn_ptr > () = IntC_ptr { new IntC {yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[3].location)} };
  }
#line 1157 "dwislpy-bison.tab.cc"
    break;

  case 33:
#line 239 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Expn_ptr > () = StrC_ptr { new StrC {yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[3].location)} };
  }
#line 1165 "dwislpy-bison.tab.cc"
    break;

  case 34:
#line 242 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Lkup_ptr { new Lkup {yystack_[0].value.as < std::string > (),lexer.locate(yystack_[0].location)} };
  }
#line 1173 "dwislpy-bison.tab.cc"
    break;

  case 35:
#line 245 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = yystack_[1].value.as < Expn_ptr > ();
  }
#line 1181 "dwislpy-bison.tab.cc"
    break;

  case 36:
#line 248 "dwislpy-bison.yy"
                 {
  yylhs.value.as < Expn_ptr > () = yystack_[2].value.as < Expn_ptr > ();
}
#line 1189 "dwislpy-bison.tab.cc"
    break;


#line 1193 "dwislpy-bison.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -38;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      37,    -2,   -28,    42,    42,    38,     7,   -38,   -38,    37,
     -38,   -38,    42,   -21,   -20,   -19,    42,    42,   -38,   -38,
     -38,   -38,   -38,   -38,    -9,   240,    42,    42,    42,   -38,
     -38,   125,    42,    42,    42,   258,   148,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    11,    18,    71,
      89,   107,    23,    24,   171,   194,   217,   -38,   266,   258,
     258,   258,   258,   258,   266,   131,   131,   131,    27,    27,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,    37,   -38,
     -38,    40,   -38
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     2,     3,     5,
       7,    13,     0,     0,     0,     0,     0,     0,    30,    28,
      29,    26,    34,    27,     0,     0,     0,     0,     0,     1,
       6,     0,     0,     0,     0,    21,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    15,    18,
      19,    20,    17,    22,    16,    23,    24,    25,    36,    36,
       8,     9,    12,    14,    36,    31,    32,    33,     0,    10,
      11,     0,     4
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -38,   -38,   -38,   -37,   -32,   -38,    39,    -4
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     6,     7,    79,     8,     9,    10,    24
  };

  const signed char
  Parser::yytable_[] =
  {
      25,    11,    12,    37,    38,    39,    40,    29,    31,    32,
      33,    34,    35,    36,    68,    41,    42,    43,    44,    45,
      46,    69,    49,    50,    51,    47,    73,    74,    54,    55,
      56,    78,    80,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,     1,     2,    82,    81,     0,    30,    26,
      13,    14,    15,     0,     3,     0,     0,     4,    16,     0,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,    70,     0,     5,    18,    19,    20,
      21,    22,    23,    37,    38,    39,    40,     0,     0,     0,
       0,     0,    71,     0,     0,    41,    42,    43,    44,    45,
      46,    37,    38,    39,    40,    53,     0,     0,     0,     0,
      72,     0,     0,    41,    42,    43,    44,    45,    46,    37,
      38,    39,    40,    53,     0,     0,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,    46,    37,    38,    39,
      40,    53,     0,     0,    38,    39,    40,     0,     0,    41,
      42,    43,    44,    45,    46,    41,    42,    52,     0,    53,
      37,    38,    39,    40,     0,    53,     0,     0,     0,     0,
       0,     0,    41,    42,    43,    44,    45,    46,     0,     0,
      57,     0,    53,    37,    38,    39,    40,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
      46,     0,     0,    75,     0,    53,    37,    38,    39,    40,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,    44,    45,    46,     0,     0,    76,     0,    53,    37,
      38,    39,    40,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,    46,     0,     0,    77,
       0,    53,    37,    38,    39,    40,     0,     0,     0,     0,
       0,     0,     0,     0,    41,    42,    43,    44,    45,    46,
      37,    38,    39,    40,    48,     0,     0,     0,     0,    38,
      39,    40,    41,    42,    43,    44,    45,    46,     0,     0,
      41,    42,    53,    44,    45,    46,     0,     0,     0,     0,
      53
  };

  const signed char
  Parser::yycheck_[] =
  {
       4,     3,    30,    12,    13,    14,    15,     0,    12,    30,
      30,    30,    16,    17,     3,    24,    25,    26,    27,    28,
      29,     3,    26,    27,    28,    34,     3,     3,    32,    33,
      34,     4,    69,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,     6,     7,     5,    78,    -1,     9,    11,
       8,     9,    10,    -1,    17,    -1,    -1,    20,    16,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,     3,    -1,    39,    35,    36,    37,
      38,    39,    40,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    -1,    24,    25,    26,    27,    28,
      29,    12,    13,    14,    15,    34,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    24,    25,    26,    27,    28,    29,    12,
      13,    14,    15,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    12,    13,    14,
      15,    34,    -1,    -1,    13,    14,    15,    -1,    -1,    24,
      25,    26,    27,    28,    29,    24,    25,    32,    -1,    34,
      12,    13,    14,    15,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    -1,    34,    12,    13,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    -1,    34,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    -1,    34,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      -1,    34,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      12,    13,    14,    15,    34,    -1,    -1,    -1,    -1,    13,
      14,    15,    24,    25,    26,    27,    28,    29,    -1,    -1,
      24,    25,    34,    27,    28,    29,    -1,    -1,    -1,    -1,
      34
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     6,     7,    17,    20,    39,    42,    43,    45,    46,
      47,     3,    30,     8,     9,    10,    16,    30,    35,    36,
      37,    38,    39,    40,    48,    48,    11,    22,    23,     0,
      47,    48,    30,    30,    30,    48,    48,    12,    13,    14,
      15,    24,    25,    26,    27,    28,    29,    34,    34,    48,
      48,    48,    32,    34,    48,    48,    48,    32,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,     3,     3,
       3,     3,     3,     3,     3,    32,    32,    32,     4,    44,
      44,    45,     5
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    41,    42,    43,    44,    45,    46,    46,    47,    47,
      47,    47,    47,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     3,     1,     2,     1,     4,     4,
       5,     5,     4,     2,     5,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     4,     4,     4,     1,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "EOFL", "error", "$undefined", "EOLN", "INDT", "DEDT", "\"pass\"",
  "\"print\"", "\"input\"", "\"int\"", "\"str\"", "\"=\"", "\"+\"",
  "\"<\"", "\"<=\"", "\"==\"", "\"not\"", "\"if\"", "\"return\"",
  "\"else\"", "\"while\"", "\"def\"", "\"+=\"", "\"-=\"", "\"and\"",
  "\"or\"", "\"-\"", "\"*\"", "\"//\"", "\"%\"", "\"(\"", "\"->\"",
  "\")\"", "\",\"", "\":\"", "\"None\"", "\"True\"", "\"False\"", "NMBR",
  "NAME", "STRG", "$accept", "main", "prgm", "nest", "blck", "stms",
  "stmt", "expn", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,   100,   100,   106,   135,   141,   148,   153,   161,   164,
     167,   170,   173,   176,   179,   185,   188,   191,   194,   197,
     200,   203,   206,   209,   212,   215,   218,   221,   224,   227,
     230,   233,   236,   239,   242,   245,   248
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
    };
    const int user_token_number_max_ = 295;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

#line 5 "dwislpy-bison.yy"
} // DWISLPY
#line 1720 "dwislpy-bison.tab.cc"

#line 253 "dwislpy-bison.yy"


void DWISLPY::Parser::error(const location_type &loc, const std::string &msg) {
    throw DwislpyError { lexer.locate(loc), msg };
}

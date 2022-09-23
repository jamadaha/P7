// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "pddlparser.tab.hh"


// Unqualified %code blocks.
#line 58 "src/pddlparser.yy"

#include "pddldriver.hh"

#line 50 "src/pddlparser.tab.cc"


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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "src/pddlparser.tab.cc"

  /// Build a parser object.
  PDDLParser::PDDLParser (PDDLDriver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  PDDLParser::~PDDLParser ()
  {}

  PDDLParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  PDDLParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  PDDLParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  PDDLParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  PDDLParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  PDDLParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  PDDLParser::symbol_kind_type
  PDDLParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  PDDLParser::stack_symbol_type::stack_symbol_type ()
  {}

  PDDLParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        value.YY_MOVE_OR_COPY< Action* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        value.YY_MOVE_OR_COPY< ActionDefBody* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        value.YY_MOVE_OR_COPY< ActionList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        value.YY_MOVE_OR_COPY< Domain* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        value.YY_MOVE_OR_COPY< DomainBody* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        value.YY_MOVE_OR_COPY< Literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_36_preconditions_list_: // "preconditions-list"
      case symbol_kind::S_37_effects_list_: // "effects-list"
      case symbol_kind::S_38_atomic_formula_: // "atomic-formula"
      case symbol_kind::S_42_literal_list_: // "literal-list"
      case symbol_kind::S_44_grounded_literal_list_: // "grounded-literal-list"
      case symbol_kind::S_45_grounded_atomic_formula_: // "grounded-atomic-formula"
      case symbol_kind::S_56_init_def_: // "init-def"
      case symbol_kind::S_57_goal_def_: // "goal-def"
      case symbol_kind::S_72_preconditions_list: // preconditions-list
      case symbol_kind::S_73_effects_list: // effects-list
      case symbol_kind::S_78_init_def: // init-def
      case symbol_kind::S_79_goal_def: // goal-def
      case symbol_kind::S_85_literal_list: // literal-list
      case symbol_kind::S_86_grounded_literal_list: // grounded-literal-list
      case symbol_kind::S_87_atomic_formula: // atomic-formula
      case symbol_kind::S_88_grounded_atomic_formula: // grounded-atomic-formula
        value.YY_MOVE_OR_COPY< LiteralList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        value.YY_MOVE_OR_COPY< ParameterList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        value.YY_MOVE_OR_COPY< Predicate* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        value.YY_MOVE_OR_COPY< PredicateList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        value.YY_MOVE_OR_COPY< Problem* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_46_requirements_def_: // "requirements-def"
      case symbol_kind::S_47_requirekeys_list_: // "requirekeys-list"
      case symbol_kind::S_52_variables_list_: // "variables-list"
      case symbol_kind::S_53_names_list_: // "names-list"
      case symbol_kind::S_55_objects_def_: // "objects-def"
      case symbol_kind::S_63_requirements_def: // requirements-def
      case symbol_kind::S_77_objects_def: // objects-def
      case symbol_kind::S_80_requirekeys_list: // requirekeys-list
      case symbol_kind::S_81_names_list: // names-list
      case symbol_kind::S_83_variables_list: // variables-list
        value.YY_MOVE_OR_COPY< StringList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        value.YY_MOVE_OR_COPY< TypeDict* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAME: // "name"
      case symbol_kind::S_VARIABLE: // "variable"
      case symbol_kind::S_REQUIREKEY: // "requirekey"
      case symbol_kind::S_28_domain_name_: // "domain-name"
      case symbol_kind::S_31_problem_name_: // "problem-name"
      case symbol_kind::S_32_domain_reference_: // "domain-reference"
      case symbol_kind::S_61_domain_name: // domain-name
      case symbol_kind::S_75_problem_name: // problem-name
      case symbol_kind::S_76_domain_reference: // domain-reference
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

  PDDLParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        value.move< Action* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        value.move< ActionDefBody* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        value.move< ActionList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        value.move< Domain* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        value.move< DomainBody* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        value.move< Literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_36_preconditions_list_: // "preconditions-list"
      case symbol_kind::S_37_effects_list_: // "effects-list"
      case symbol_kind::S_38_atomic_formula_: // "atomic-formula"
      case symbol_kind::S_42_literal_list_: // "literal-list"
      case symbol_kind::S_44_grounded_literal_list_: // "grounded-literal-list"
      case symbol_kind::S_45_grounded_atomic_formula_: // "grounded-atomic-formula"
      case symbol_kind::S_56_init_def_: // "init-def"
      case symbol_kind::S_57_goal_def_: // "goal-def"
      case symbol_kind::S_72_preconditions_list: // preconditions-list
      case symbol_kind::S_73_effects_list: // effects-list
      case symbol_kind::S_78_init_def: // init-def
      case symbol_kind::S_79_goal_def: // goal-def
      case symbol_kind::S_85_literal_list: // literal-list
      case symbol_kind::S_86_grounded_literal_list: // grounded-literal-list
      case symbol_kind::S_87_atomic_formula: // atomic-formula
      case symbol_kind::S_88_grounded_atomic_formula: // grounded-atomic-formula
        value.move< LiteralList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        value.move< ParameterList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        value.move< Predicate* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        value.move< PredicateList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        value.move< Problem* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_46_requirements_def_: // "requirements-def"
      case symbol_kind::S_47_requirekeys_list_: // "requirekeys-list"
      case symbol_kind::S_52_variables_list_: // "variables-list"
      case symbol_kind::S_53_names_list_: // "names-list"
      case symbol_kind::S_55_objects_def_: // "objects-def"
      case symbol_kind::S_63_requirements_def: // requirements-def
      case symbol_kind::S_77_objects_def: // objects-def
      case symbol_kind::S_80_requirekeys_list: // requirekeys-list
      case symbol_kind::S_81_names_list: // names-list
      case symbol_kind::S_83_variables_list: // variables-list
        value.move< StringList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        value.move< TypeDict* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAME: // "name"
      case symbol_kind::S_VARIABLE: // "variable"
      case symbol_kind::S_REQUIREKEY: // "requirekey"
      case symbol_kind::S_28_domain_name_: // "domain-name"
      case symbol_kind::S_31_problem_name_: // "problem-name"
      case symbol_kind::S_32_domain_reference_: // "domain-reference"
      case symbol_kind::S_61_domain_name: // domain-name
      case symbol_kind::S_75_problem_name: // problem-name
      case symbol_kind::S_76_domain_reference: // domain-reference
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  PDDLParser::stack_symbol_type&
  PDDLParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        value.copy< Action* > (that.value);
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        value.copy< ActionDefBody* > (that.value);
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        value.copy< ActionList* > (that.value);
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        value.copy< Domain* > (that.value);
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        value.copy< DomainBody* > (that.value);
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        value.copy< Literal* > (that.value);
        break;

      case symbol_kind::S_36_preconditions_list_: // "preconditions-list"
      case symbol_kind::S_37_effects_list_: // "effects-list"
      case symbol_kind::S_38_atomic_formula_: // "atomic-formula"
      case symbol_kind::S_42_literal_list_: // "literal-list"
      case symbol_kind::S_44_grounded_literal_list_: // "grounded-literal-list"
      case symbol_kind::S_45_grounded_atomic_formula_: // "grounded-atomic-formula"
      case symbol_kind::S_56_init_def_: // "init-def"
      case symbol_kind::S_57_goal_def_: // "goal-def"
      case symbol_kind::S_72_preconditions_list: // preconditions-list
      case symbol_kind::S_73_effects_list: // effects-list
      case symbol_kind::S_78_init_def: // init-def
      case symbol_kind::S_79_goal_def: // goal-def
      case symbol_kind::S_85_literal_list: // literal-list
      case symbol_kind::S_86_grounded_literal_list: // grounded-literal-list
      case symbol_kind::S_87_atomic_formula: // atomic-formula
      case symbol_kind::S_88_grounded_atomic_formula: // grounded-atomic-formula
        value.copy< LiteralList* > (that.value);
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        value.copy< ParameterList* > (that.value);
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        value.copy< Predicate* > (that.value);
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        value.copy< PredicateList* > (that.value);
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        value.copy< Problem* > (that.value);
        break;

      case symbol_kind::S_46_requirements_def_: // "requirements-def"
      case symbol_kind::S_47_requirekeys_list_: // "requirekeys-list"
      case symbol_kind::S_52_variables_list_: // "variables-list"
      case symbol_kind::S_53_names_list_: // "names-list"
      case symbol_kind::S_55_objects_def_: // "objects-def"
      case symbol_kind::S_63_requirements_def: // requirements-def
      case symbol_kind::S_77_objects_def: // objects-def
      case symbol_kind::S_80_requirekeys_list: // requirekeys-list
      case symbol_kind::S_81_names_list: // names-list
      case symbol_kind::S_83_variables_list: // variables-list
        value.copy< StringList* > (that.value);
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        value.copy< TypeDict* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_NAME: // "name"
      case symbol_kind::S_VARIABLE: // "variable"
      case symbol_kind::S_REQUIREKEY: // "requirekey"
      case symbol_kind::S_28_domain_name_: // "domain-name"
      case symbol_kind::S_31_problem_name_: // "problem-name"
      case symbol_kind::S_32_domain_reference_: // "domain-reference"
      case symbol_kind::S_61_domain_name: // domain-name
      case symbol_kind::S_75_problem_name: // problem-name
      case symbol_kind::S_76_domain_reference: // domain-reference
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  PDDLParser::stack_symbol_type&
  PDDLParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        value.move< Action* > (that.value);
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        value.move< ActionDefBody* > (that.value);
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        value.move< ActionList* > (that.value);
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        value.move< Domain* > (that.value);
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        value.move< DomainBody* > (that.value);
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        value.move< Literal* > (that.value);
        break;

      case symbol_kind::S_36_preconditions_list_: // "preconditions-list"
      case symbol_kind::S_37_effects_list_: // "effects-list"
      case symbol_kind::S_38_atomic_formula_: // "atomic-formula"
      case symbol_kind::S_42_literal_list_: // "literal-list"
      case symbol_kind::S_44_grounded_literal_list_: // "grounded-literal-list"
      case symbol_kind::S_45_grounded_atomic_formula_: // "grounded-atomic-formula"
      case symbol_kind::S_56_init_def_: // "init-def"
      case symbol_kind::S_57_goal_def_: // "goal-def"
      case symbol_kind::S_72_preconditions_list: // preconditions-list
      case symbol_kind::S_73_effects_list: // effects-list
      case symbol_kind::S_78_init_def: // init-def
      case symbol_kind::S_79_goal_def: // goal-def
      case symbol_kind::S_85_literal_list: // literal-list
      case symbol_kind::S_86_grounded_literal_list: // grounded-literal-list
      case symbol_kind::S_87_atomic_formula: // atomic-formula
      case symbol_kind::S_88_grounded_atomic_formula: // grounded-atomic-formula
        value.move< LiteralList* > (that.value);
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        value.move< ParameterList* > (that.value);
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        value.move< Predicate* > (that.value);
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        value.move< PredicateList* > (that.value);
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        value.move< Problem* > (that.value);
        break;

      case symbol_kind::S_46_requirements_def_: // "requirements-def"
      case symbol_kind::S_47_requirekeys_list_: // "requirekeys-list"
      case symbol_kind::S_52_variables_list_: // "variables-list"
      case symbol_kind::S_53_names_list_: // "names-list"
      case symbol_kind::S_55_objects_def_: // "objects-def"
      case symbol_kind::S_63_requirements_def: // requirements-def
      case symbol_kind::S_77_objects_def: // objects-def
      case symbol_kind::S_80_requirekeys_list: // requirekeys-list
      case symbol_kind::S_81_names_list: // names-list
      case symbol_kind::S_83_variables_list: // variables-list
        value.move< StringList* > (that.value);
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        value.move< TypeDict* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_NAME: // "name"
      case symbol_kind::S_VARIABLE: // "variable"
      case symbol_kind::S_REQUIREKEY: // "requirekey"
      case symbol_kind::S_28_domain_name_: // "domain-name"
      case symbol_kind::S_31_problem_name_: // "problem-name"
      case symbol_kind::S_32_domain_reference_: // "domain-reference"
      case symbol_kind::S_61_domain_name: // domain-name
      case symbol_kind::S_75_problem_name: // problem-name
      case symbol_kind::S_76_domain_reference: // domain-reference
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
  PDDLParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  PDDLParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        switch (yykind)
    {
      case symbol_kind::S_NAME: // "name"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 737 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_NUMBER: // "number"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < int > (); }
#line 743 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_VARIABLE: // "variable"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 749 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_REQUIREKEY: // "requirekey"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 755 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Domain* > (); }
#line 761 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_28_domain_name_: // "domain-name"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 767 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < DomainBody* > (); }
#line 773 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Problem* > (); }
#line 779 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_31_problem_name_: // "problem-name"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 785 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_32_domain_reference_: // "domain-reference"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 791 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_33_actions_: // "actions"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < ActionList* > (); }
#line 797 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_34_action_def_: // "action-def"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Action* > (); }
#line 803 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < ActionDefBody* > (); }
#line 809 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_36_preconditions_list_: // "preconditions-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 815 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_37_effects_list_: // "effects-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 821 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_38_atomic_formula_: // "atomic-formula"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 827 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Predicate* > (); }
#line 833 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Predicate* > (); }
#line 839 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_41_literal_: // "literal"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Literal* > (); }
#line 845 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_42_literal_list_: // "literal-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 851 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Literal* > (); }
#line 857 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_44_grounded_literal_list_: // "grounded-literal-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 863 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_45_grounded_atomic_formula_: // "grounded-atomic-formula"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 869 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_46_requirements_def_: // "requirements-def"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 875 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_47_requirekeys_list_: // "requirekeys-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 881 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < PredicateList* > (); }
#line 887 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_49_predicates_list_: // "predicates-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < PredicateList* > (); }
#line 893 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < ParameterList* > (); }
#line 899 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < TypeDict* > (); }
#line 905 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_52_variables_list_: // "variables-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 911 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_53_names_list_: // "names-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 917 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < TypeDict* > (); }
#line 923 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_55_objects_def_: // "objects-def"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 929 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_56_init_def_: // "init-def"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 935 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_57_goal_def_: // "goal-def"
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 941 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_60_domain_def: // domain-def
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Domain* > (); }
#line 947 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_61_domain_name: // domain-name
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 953 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_62_domain_body: // domain-body
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < DomainBody* > (); }
#line 959 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_63_requirements_def: // requirements-def
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 965 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_66_predicates_def: // predicates-def
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < PredicateList* > (); }
#line 971 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_actions: // actions
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < ActionList* > (); }
#line 977 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_68_action_def: // action-def
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Action* > (); }
#line 983 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_69_predicates_list: // predicates-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < PredicateList* > (); }
#line 989 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_70_parameters_list: // parameters-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < ParameterList* > (); }
#line 995 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_71_action_def_body: // action-def-body
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < ActionDefBody* > (); }
#line 1001 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_72_preconditions_list: // preconditions-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 1007 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_73_effects_list: // effects-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 1013 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_74_problem_def: // problem-def
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Problem* > (); }
#line 1019 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_75_problem_name: // problem-name
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 1025 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_76_domain_reference: // domain-reference
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 1031 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_77_objects_def: // objects-def
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 1037 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_78_init_def: // init-def
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 1043 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_79_goal_def: // goal-def
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 1049 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_80_requirekeys_list: // requirekeys-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 1055 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_81_names_list: // names-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 1061 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_82_typed_names_list: // typed-names-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < TypeDict* > (); }
#line 1067 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_83_variables_list: // variables-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < StringList* > (); }
#line 1073 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < TypeDict* > (); }
#line 1079 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_85_literal_list: // literal-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 1085 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_86_grounded_literal_list: // grounded-literal-list
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 1091 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_87_atomic_formula: // atomic-formula
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 1097 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_88_grounded_atomic_formula: // grounded-atomic-formula
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < LiteralList* > (); }
#line 1103 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_predicate: // predicate
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Predicate* > (); }
#line 1109 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Predicate* > (); }
#line 1115 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_literal: // literal
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Literal* > (); }
#line 1121 "src/pddlparser.tab.cc"
        break;

      case symbol_kind::S_92_grounded_literal: // grounded-literal
#line 136 "src/pddlparser.yy"
                 { yyoutput << yysym.value.template as < Literal* > (); }
#line 1127 "src/pddlparser.tab.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  PDDLParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  PDDLParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  PDDLParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  PDDLParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  PDDLParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  PDDLParser::debug_level_type
  PDDLParser::debug_level () const
  {
    return yydebug_;
  }

  void
  PDDLParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  PDDLParser::state_type
  PDDLParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  PDDLParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  PDDLParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  PDDLParser::operator() ()
  {
    return parse ();
  }

  int
  PDDLParser::parse ()
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


    // User initialization code.
#line 49 "src/pddlparser.yy"
{
// Initialize the initial location.
yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 1252 "src/pddlparser.tab.cc"


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
    YY_STACK_PRINT ();

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
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
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

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
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
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        yylhs.value.emplace< Action* > ();
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        yylhs.value.emplace< ActionDefBody* > ();
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        yylhs.value.emplace< ActionList* > ();
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        yylhs.value.emplace< Domain* > ();
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        yylhs.value.emplace< DomainBody* > ();
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        yylhs.value.emplace< Literal* > ();
        break;

      case symbol_kind::S_36_preconditions_list_: // "preconditions-list"
      case symbol_kind::S_37_effects_list_: // "effects-list"
      case symbol_kind::S_38_atomic_formula_: // "atomic-formula"
      case symbol_kind::S_42_literal_list_: // "literal-list"
      case symbol_kind::S_44_grounded_literal_list_: // "grounded-literal-list"
      case symbol_kind::S_45_grounded_atomic_formula_: // "grounded-atomic-formula"
      case symbol_kind::S_56_init_def_: // "init-def"
      case symbol_kind::S_57_goal_def_: // "goal-def"
      case symbol_kind::S_72_preconditions_list: // preconditions-list
      case symbol_kind::S_73_effects_list: // effects-list
      case symbol_kind::S_78_init_def: // init-def
      case symbol_kind::S_79_goal_def: // goal-def
      case symbol_kind::S_85_literal_list: // literal-list
      case symbol_kind::S_86_grounded_literal_list: // grounded-literal-list
      case symbol_kind::S_87_atomic_formula: // atomic-formula
      case symbol_kind::S_88_grounded_atomic_formula: // grounded-atomic-formula
        yylhs.value.emplace< LiteralList* > ();
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        yylhs.value.emplace< ParameterList* > ();
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        yylhs.value.emplace< Predicate* > ();
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        yylhs.value.emplace< PredicateList* > ();
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        yylhs.value.emplace< Problem* > ();
        break;

      case symbol_kind::S_46_requirements_def_: // "requirements-def"
      case symbol_kind::S_47_requirekeys_list_: // "requirekeys-list"
      case symbol_kind::S_52_variables_list_: // "variables-list"
      case symbol_kind::S_53_names_list_: // "names-list"
      case symbol_kind::S_55_objects_def_: // "objects-def"
      case symbol_kind::S_63_requirements_def: // requirements-def
      case symbol_kind::S_77_objects_def: // objects-def
      case symbol_kind::S_80_requirekeys_list: // requirekeys-list
      case symbol_kind::S_81_names_list: // names-list
      case symbol_kind::S_83_variables_list: // variables-list
        yylhs.value.emplace< StringList* > ();
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        yylhs.value.emplace< TypeDict* > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_NAME: // "name"
      case symbol_kind::S_VARIABLE: // "variable"
      case symbol_kind::S_REQUIREKEY: // "requirekey"
      case symbol_kind::S_28_domain_name_: // "domain-name"
      case symbol_kind::S_31_problem_name_: // "problem-name"
      case symbol_kind::S_32_domain_reference_: // "domain-reference"
      case symbol_kind::S_61_domain_name: // domain-name
      case symbol_kind::S_75_problem_name: // problem-name
      case symbol_kind::S_76_domain_reference: // domain-reference
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
  case 2: // pddl: domain-def
#line 145 "src/pddlparser.yy"
                  { driver.domain  = yystack_[0].value.as < Domain* > (); }
#line 1501 "src/pddlparser.tab.cc"
    break;

  case 3: // pddl: problem-def
#line 146 "src/pddlparser.yy"
                  { driver.problem = yystack_[0].value.as < Problem* > (); }
#line 1507 "src/pddlparser.tab.cc"
    break;

  case 4: // domain-def: "(" "define" domain-name domain-body ")"
#line 150 "src/pddlparser.yy"
    {
        yylhs.value.as < Domain* > () = new Domain(yystack_[2].value.as < std::string > ());
        yylhs.value.as < Domain* > ()->set_requirements(yystack_[1].value.as < DomainBody* > ()->requirements);
        yylhs.value.as < Domain* > ()->set_predicates(yystack_[1].value.as < DomainBody* > ()->predicates);
        yylhs.value.as < Domain* > ()->set_actions(yystack_[1].value.as < DomainBody* > ()->actions);
        delete yystack_[1].value.as < DomainBody* > ();
    }
#line 1519 "src/pddlparser.tab.cc"
    break;

  case 5: // domain-name: "(" "domain" "name" ")"
#line 158 "src/pddlparser.yy"
                                       { yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > (); }
#line 1525 "src/pddlparser.tab.cc"
    break;

  case 6: // domain-body: requirements-def predicates-def actions
#line 161 "src/pddlparser.yy"
                                              { yylhs.value.as < DomainBody* > () = new DomainBody{yystack_[2].value.as < StringList* > (), yystack_[1].value.as < PredicateList* > (), yystack_[0].value.as < ActionList* > ()}; }
#line 1531 "src/pddlparser.tab.cc"
    break;

  case 7: // domain-body: requirements-def constants predicates-def actions
#line 162 "src/pddlparser.yy"
                                                        { yylhs.value.as < DomainBody* > () = new DomainBody{yystack_[3].value.as < StringList* > (), yystack_[1].value.as < PredicateList* > (), yystack_[0].value.as < ActionList* > ()}; }
#line 1537 "src/pddlparser.tab.cc"
    break;

  case 8: // domain-body: requirements-def types predicates-def actions
#line 163 "src/pddlparser.yy"
                                                    { yylhs.value.as < DomainBody* > () = new DomainBody{yystack_[3].value.as < StringList* > (), yystack_[1].value.as < PredicateList* > (), yystack_[0].value.as < ActionList* > ()}; }
#line 1543 "src/pddlparser.tab.cc"
    break;

  case 9: // domain-body: requirements-def types constants predicates-def actions
#line 164 "src/pddlparser.yy"
                                                              { yylhs.value.as < DomainBody* > () = new DomainBody{yystack_[4].value.as < StringList* > (), yystack_[1].value.as < PredicateList* > (), yystack_[0].value.as < ActionList* > ()}; }
#line 1549 "src/pddlparser.tab.cc"
    break;

  case 10: // requirements-def: "(" "requirements" requirekeys-list ")"
#line 167 "src/pddlparser.yy"
                                                              { yylhs.value.as < StringList* > () = yystack_[1].value.as < StringList* > (); }
#line 1555 "src/pddlparser.tab.cc"
    break;

  case 11: // types: "(" "types" names-list ")"
#line 170 "src/pddlparser.yy"
                                     {}
#line 1561 "src/pddlparser.tab.cc"
    break;

  case 12: // types: "(" "types" typed-names-list ")"
#line 171 "src/pddlparser.yy"
                                           {}
#line 1567 "src/pddlparser.tab.cc"
    break;

  case 13: // constants: "(" "constants" names-list ")"
#line 175 "src/pddlparser.yy"
                                         {}
#line 1573 "src/pddlparser.tab.cc"
    break;

  case 14: // constants: "(" "constants" typed-names-list ")"
#line 176 "src/pddlparser.yy"
                                               {}
#line 1579 "src/pddlparser.tab.cc"
    break;

  case 15: // predicates-def: "(" "predicates" predicates-list ")"
#line 179 "src/pddlparser.yy"
                                                         { yylhs.value.as < PredicateList* > () = yystack_[1].value.as < PredicateList* > (); }
#line 1585 "src/pddlparser.tab.cc"
    break;

  case 16: // actions: action-def
#line 182 "src/pddlparser.yy"
                         { yylhs.value.as < ActionList* > () = new ActionList; yylhs.value.as < ActionList* > ()->push_back(yystack_[0].value.as < Action* > ()); }
#line 1591 "src/pddlparser.tab.cc"
    break;

  case 17: // actions: actions action-def
#line 183 "src/pddlparser.yy"
                         { yystack_[1].value.as < ActionList* > ()->push_back(yystack_[0].value.as < Action* > ()); yylhs.value.as < ActionList* > () = yystack_[1].value.as < ActionList* > (); }
#line 1597 "src/pddlparser.tab.cc"
    break;

  case 18: // action-def: "(" "action" "name" parameters-list action-def-body ")"
#line 187 "src/pddlparser.yy"
    {
        yylhs.value.as < Action* > () = new Action(yystack_[3].value.as < std::string > (), yystack_[2].value.as < ParameterList* > (), yystack_[1].value.as < ActionDefBody* > ()->first, yystack_[1].value.as < ActionDefBody* > ()->second);
        delete yystack_[1].value.as < ActionDefBody* > ();
    }
#line 1606 "src/pddlparser.tab.cc"
    break;

  case 19: // predicates-list: predicate
#line 193 "src/pddlparser.yy"
                { yylhs.value.as < PredicateList* > () = new PredicateList; yylhs.value.as < PredicateList* > ()->push_back(yystack_[0].value.as < Predicate* > ()); }
#line 1612 "src/pddlparser.tab.cc"
    break;

  case 20: // predicates-list: predicates-list predicate
#line 194 "src/pddlparser.yy"
                                { yystack_[1].value.as < PredicateList* > ()->push_back(yystack_[0].value.as < Predicate* > ()); yylhs.value.as < PredicateList* > () = yystack_[1].value.as < PredicateList* > ();}
#line 1618 "src/pddlparser.tab.cc"
    break;

  case 21: // parameters-list: "parameters" "(" typed-variables-list ")"
#line 199 "src/pddlparser.yy"
        {
            StringList *parameters = new StringList();
            for (const auto& param : *yystack_[1].value.as < TypeDict* > ()) {
                parameters->push_back(param.first);
            }
            yylhs.value.as < ParameterList* > () = new ParameterList(parameters, yystack_[1].value.as < TypeDict* > ());
        }
#line 1630 "src/pddlparser.tab.cc"
    break;

  case 22: // parameters-list: "parameters" "(" variables-list ")"
#line 207 "src/pddlparser.yy"
        {
            yylhs.value.as < ParameterList* > () = new ParameterList(yystack_[1].value.as < StringList* > (), nullptr);
        }
#line 1638 "src/pddlparser.tab.cc"
    break;

  case 23: // parameters-list: "parameters" "(" ")"
#line 211 "src/pddlparser.yy"
        {
            yylhs.value.as < ParameterList* > () = new ParameterList(nullptr, nullptr);
        }
#line 1646 "src/pddlparser.tab.cc"
    break;

  case 24: // action-def-body: preconditions-list effects-list
#line 217 "src/pddlparser.yy"
    {
        yylhs.value.as < ActionDefBody* > () = new ActionDefBody(yystack_[1].value.as < LiteralList* > (), yystack_[0].value.as < LiteralList* > ());
    }
#line 1654 "src/pddlparser.tab.cc"
    break;

  case 25: // preconditions-list: "preconditions" atomic-formula
#line 221 "src/pddlparser.yy"
                                                 { yylhs.value.as < LiteralList* > () = yystack_[0].value.as < LiteralList* > (); }
#line 1660 "src/pddlparser.tab.cc"
    break;

  case 26: // effects-list: "effects" atomic-formula
#line 223 "src/pddlparser.yy"
                                     { yylhs.value.as < LiteralList* > () = yystack_[0].value.as < LiteralList* > (); }
#line 1666 "src/pddlparser.tab.cc"
    break;

  case 27: // problem-def: "(" "define" problem-name domain-reference objects-def init-def goal-def ")"
#line 226 "src/pddlparser.yy"
    {
        yylhs.value.as < Problem* > () = new Problem(yystack_[5].value.as < std::string > (), yystack_[4].value.as < std::string > ());
        yylhs.value.as < Problem* > ()->set_objects(yystack_[3].value.as < StringList* > ());
        yylhs.value.as < Problem* > ()->set_init_state(yystack_[2].value.as < LiteralList* > ());
        yylhs.value.as < Problem* > ()->set_goal_state(yystack_[1].value.as < LiteralList* > ());
    }
#line 1677 "src/pddlparser.tab.cc"
    break;

  case 28: // problem-name: "(" "problem" "name" ")"
#line 233 "src/pddlparser.yy"
                                         { yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > (); }
#line 1683 "src/pddlparser.tab.cc"
    break;

  case 29: // domain-reference: "(" "domain" "name" ")"
#line 235 "src/pddlparser.yy"
                                            { yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > (); }
#line 1689 "src/pddlparser.tab.cc"
    break;

  case 30: // objects-def: "(" "objects" names-list ")"
#line 237 "src/pddlparser.yy"
                                              { yylhs.value.as < StringList* > () = yystack_[1].value.as < StringList* > (); }
#line 1695 "src/pddlparser.tab.cc"
    break;

  case 31: // init-def: "(" "init" grounded-literal-list ")"
#line 239 "src/pddlparser.yy"
                                                   { yylhs.value.as < LiteralList* > () = yystack_[1].value.as < LiteralList* > (); }
#line 1701 "src/pddlparser.tab.cc"
    break;

  case 32: // goal-def: "(" "goal" grounded-atomic-formula ")"
#line 241 "src/pddlparser.yy"
                                                     { yylhs.value.as < LiteralList* > () = yystack_[1].value.as < LiteralList* > (); }
#line 1707 "src/pddlparser.tab.cc"
    break;

  case 33: // requirekeys-list: "requirekey"
#line 244 "src/pddlparser.yy"
                 { yylhs.value.as < StringList* > () = new StringList; yylhs.value.as < StringList* > ()->push_back(yystack_[0].value.as < std::string > ()); }
#line 1713 "src/pddlparser.tab.cc"
    break;

  case 34: // requirekeys-list: requirekeys-list "requirekey"
#line 245 "src/pddlparser.yy"
                                  { yystack_[1].value.as < StringList* > ()->push_back(yystack_[0].value.as < std::string > ()); yylhs.value.as < StringList* > () = yystack_[1].value.as < StringList* > (); }
#line 1719 "src/pddlparser.tab.cc"
    break;

  case 35: // names-list: "name"
#line 249 "src/pddlparser.yy"
           { yylhs.value.as < StringList* > () = new StringList; yylhs.value.as < StringList* > ()->push_back(yystack_[0].value.as < std::string > ()); }
#line 1725 "src/pddlparser.tab.cc"
    break;

  case 36: // names-list: names-list "name"
#line 250 "src/pddlparser.yy"
                      { yystack_[1].value.as < StringList* > ()->push_back(yystack_[0].value.as < std::string > ()); yylhs.value.as < StringList* > () = yystack_[1].value.as < StringList* > (); }
#line 1731 "src/pddlparser.tab.cc"
    break;

  case 37: // typed-names-list: names-list "-" "name"
#line 254 "src/pddlparser.yy"
                             {}
#line 1737 "src/pddlparser.tab.cc"
    break;

  case 38: // typed-names-list: typed-names-list names-list "-" "name"
#line 255 "src/pddlparser.yy"
                                              {}
#line 1743 "src/pddlparser.tab.cc"
    break;

  case 39: // variables-list: "variable"
#line 259 "src/pddlparser.yy"
               { yylhs.value.as < StringList* > () = new StringList; yylhs.value.as < StringList* > ()->push_back(yystack_[0].value.as < std::string > ()); }
#line 1749 "src/pddlparser.tab.cc"
    break;

  case 40: // variables-list: variables-list "variable"
#line 260 "src/pddlparser.yy"
                              { yystack_[1].value.as < StringList* > ()->push_back(yystack_[0].value.as < std::string > ()); yylhs.value.as < StringList* > () = yystack_[1].value.as < StringList* > (); }
#line 1755 "src/pddlparser.tab.cc"
    break;

  case 41: // typed-variables-list: variables-list "-" "name"
#line 265 "src/pddlparser.yy"
        {
            std::string type(yystack_[0].value.as < std::string > ());
            yylhs.value.as < TypeDict* > () = new TypeDict;
            for (const auto& var : *yystack_[2].value.as < StringList* > ()) {
                (*yylhs.value.as < TypeDict* > ())[var] = type;
            }
        }
#line 1767 "src/pddlparser.tab.cc"
    break;

  case 42: // typed-variables-list: typed-variables-list variables-list "-" "name"
#line 273 "src/pddlparser.yy"
        {
            std::string type(yystack_[0].value.as < std::string > ());
            for (const auto& var : *yystack_[2].value.as < StringList* > ()) {
                (*yystack_[3].value.as < TypeDict* > ())[var] = type;
            }
            yylhs.value.as < TypeDict* > () = yystack_[3].value.as < TypeDict* > ();
        }
#line 1779 "src/pddlparser.tab.cc"
    break;

  case 43: // literal-list: literal
#line 283 "src/pddlparser.yy"
              { yylhs.value.as < LiteralList* > () = new LiteralList; yylhs.value.as < LiteralList* > ()->push_back(yystack_[0].value.as < Literal* > ()); }
#line 1785 "src/pddlparser.tab.cc"
    break;

  case 44: // literal-list: literal-list literal
#line 284 "src/pddlparser.yy"
                           { yystack_[1].value.as < LiteralList* > ()->push_back(yystack_[0].value.as < Literal* > ()); yylhs.value.as < LiteralList* > () = yystack_[1].value.as < LiteralList* > (); }
#line 1791 "src/pddlparser.tab.cc"
    break;

  case 45: // grounded-literal-list: grounded-literal
#line 288 "src/pddlparser.yy"
                       { yylhs.value.as < LiteralList* > () = new LiteralList; yylhs.value.as < LiteralList* > ()->push_back(yystack_[0].value.as < Literal* > ()); }
#line 1797 "src/pddlparser.tab.cc"
    break;

  case 46: // grounded-literal-list: grounded-literal-list grounded-literal
#line 289 "src/pddlparser.yy"
                                             { yystack_[1].value.as < LiteralList* > ()->push_back(yystack_[0].value.as < Literal* > ()); yylhs.value.as < LiteralList* > () = yystack_[1].value.as < LiteralList* > (); }
#line 1803 "src/pddlparser.tab.cc"
    break;

  case 47: // atomic-formula: literal
#line 293 "src/pddlparser.yy"
              { yylhs.value.as < LiteralList* > () = new LiteralList; yylhs.value.as < LiteralList* > ()->push_back(yystack_[0].value.as < Literal* > ()); }
#line 1809 "src/pddlparser.tab.cc"
    break;

  case 48: // atomic-formula: "(" "and" literal-list ")"
#line 294 "src/pddlparser.yy"
                                     { yylhs.value.as < LiteralList* > () = yystack_[1].value.as < LiteralList* > (); }
#line 1815 "src/pddlparser.tab.cc"
    break;

  case 49: // grounded-atomic-formula: grounded-literal
#line 298 "src/pddlparser.yy"
                       { yylhs.value.as < LiteralList* > () = new LiteralList; yylhs.value.as < LiteralList* > ()->push_back(yystack_[0].value.as < Literal* > ()); }
#line 1821 "src/pddlparser.tab.cc"
    break;

  case 50: // grounded-atomic-formula: "(" "and" grounded-literal-list ")"
#line 299 "src/pddlparser.yy"
                                              { yylhs.value.as < LiteralList* > () = yystack_[1].value.as < LiteralList* > (); }
#line 1827 "src/pddlparser.tab.cc"
    break;

  case 51: // predicate: "(" "name" typed-variables-list ")"
#line 304 "src/pddlparser.yy"
        {
            StringList *vars = new StringList;
            for (const auto& var : *yystack_[1].value.as < TypeDict* > ()) {
                vars->push_back(var.first);
            }
            auto args = new ArgumentList(vars, yystack_[1].value.as < TypeDict* > ());
            yylhs.value.as < Predicate* > () = new Predicate(yystack_[2].value.as < std::string > (), args);
        }
#line 1840 "src/pddlparser.tab.cc"
    break;

  case 52: // predicate: "(" "name" variables-list ")"
#line 313 "src/pddlparser.yy"
        {
            auto args = new ArgumentList(yystack_[1].value.as < StringList* > (), nullptr);
            yylhs.value.as < Predicate* > () = new Predicate(yystack_[2].value.as < std::string > (), args);
        }
#line 1849 "src/pddlparser.tab.cc"
    break;

  case 53: // predicate: "(" "=" "variable" "variable" ")"
#line 318 "src/pddlparser.yy"
        {
            StringList *vars = new StringList(2);
            (*vars)[0] = yystack_[2].value.as < std::string > ();
            (*vars)[1] = yystack_[1].value.as < std::string > ();
            auto args = new ArgumentList(vars, nullptr);
            yylhs.value.as < Predicate* > () = new Predicate("=", args);
        }
#line 1861 "src/pddlparser.tab.cc"
    break;

  case 54: // grounded-predicate: "(" "name" names-list ")"
#line 329 "src/pddlparser.yy"
        {
            auto args = new ArgumentList(yystack_[1].value.as < StringList* > (), nullptr);
            yylhs.value.as < Predicate* > () = new Predicate(yystack_[2].value.as < std::string > (), args);
        }
#line 1870 "src/pddlparser.tab.cc"
    break;

  case 55: // grounded-predicate: "(" "=" "name" "name" ")"
#line 334 "src/pddlparser.yy"
        {
            StringList *vars = new StringList(2);
            (*vars)[0] = yystack_[2].value.as < std::string > ();
            (*vars)[1] = yystack_[1].value.as < std::string > ();
            auto args = new ArgumentList(vars, nullptr);
            yylhs.value.as < Predicate* > () = new Predicate("=", args);
        }
#line 1882 "src/pddlparser.tab.cc"
    break;

  case 56: // literal: predicate
#line 344 "src/pddlparser.yy"
                { yylhs.value.as < Literal* > () = new Literal(yystack_[0].value.as < Predicate* > (), true); }
#line 1888 "src/pddlparser.tab.cc"
    break;

  case 57: // literal: "(" "not" predicate ")"
#line 345 "src/pddlparser.yy"
                                  { yylhs.value.as < Literal* > () = new Literal(yystack_[1].value.as < Predicate* > (), false); }
#line 1894 "src/pddlparser.tab.cc"
    break;

  case 58: // grounded-literal: grounded-predicate
#line 349 "src/pddlparser.yy"
                         { yylhs.value.as < Literal* > () = new Literal(yystack_[0].value.as < Predicate* > (), true); }
#line 1900 "src/pddlparser.tab.cc"
    break;

  case 59: // grounded-literal: "(" "not" grounded-predicate ")"
#line 350 "src/pddlparser.yy"
                                           { yylhs.value.as < Literal* > () = new Literal(yystack_[1].value.as < Predicate* > (), false); }
#line 1906 "src/pddlparser.tab.cc"
    break;


#line 1910 "src/pddlparser.tab.cc"

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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
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
    {
      stack_symbol_type error_token;

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
    YY_STACK_PRINT ();
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
  PDDLParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  PDDLParser::yytnamerr_ (const char *yystr)
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

  std::string
  PDDLParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // PDDLParser::context.
  PDDLParser::context::context (const PDDLParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  PDDLParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  PDDLParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
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

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  PDDLParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

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
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char PDDLParser::yypact_ninf_ = -127;

  const signed char PDDLParser::yytable_ninf_ = -1;

  const short
  PDDLParser::yypact_[] =
  {
      21,    55,    76,  -127,  -127,    64,  -127,    74,    73,    75,
      51,    77,    88,    78,    81,    92,    82,    83,    84,    80,
    -127,    53,    89,    90,    91,    85,    86,    93,  -127,  -127,
    -127,     5,    94,    94,    95,    72,    90,    91,   103,    91,
      87,    91,  -127,    97,    94,    96,    99,  -127,  -127,  -127,
      42,    31,    46,    49,    -8,    62,  -127,    91,    91,    91,
      98,  -127,  -127,    50,   100,    79,   101,  -127,   102,  -127,
    -127,    63,  -127,  -127,   104,   105,  -127,  -127,    91,   112,
    -127,    17,    67,  -127,  -127,   106,  -127,  -127,   108,   107,
    -127,    23,    13,   113,   115,   114,   116,    94,  -127,  -127,
       2,   117,  -127,  -127,   119,  -127,   118,  -127,  -127,    34,
      28,   122,   123,   111,    -4,   124,   120,    54,   100,  -127,
    -127,  -127,   125,  -127,    25,    30,    14,  -127,  -127,  -127,
    -127,   122,  -127,  -127,   126,  -127,    69,  -127,  -127,  -127,
     129,    95,  -127,  -127,  -127,    20,    71,  -127,   130,  -127,
    -127,  -127
  };

  const signed char
  PDDLParser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,     0,     0,     0,     5,    28,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,    16,     0,     0,     0,     0,    10,    34,    35,
       0,     0,     0,     0,     0,     0,    19,     0,     8,     7,
       0,    17,    29,     0,     0,     0,     0,    11,     0,    36,
      12,     0,    13,    14,     0,     0,    15,    20,     9,     0,
      30,     0,     0,    58,    45,     0,    27,    37,     0,     0,
      39,     0,     0,     0,     0,     0,     0,     0,    31,    46,
       0,     0,    49,    38,     0,    52,     0,    40,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      53,    41,     0,    23,     0,     0,     0,    25,    56,    47,
      18,     0,    24,    59,     0,    54,     0,    42,    22,    21,
       0,     0,    26,    55,    50,     0,     0,    43,     0,    48,
      44,    57
  };

  const short
  PDDLParser::yypgoto_[] =
  {
    -127,  -127,  -127,  -127,  -127,  -127,  -127,   128,   -12,   -30,
     -36,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,   -31,   121,   -71,     6,  -127,    10,     4,
    -127,   -34,    41,  -126,   -79
  };

  const unsigned char
  PDDLParser::yydefgoto_[] =
  {
       0,     2,     3,     8,    13,    14,    22,    23,    24,    41,
      42,    55,    94,   112,   113,   132,     4,     9,    16,    27,
      46,    66,    31,    71,    51,   109,    92,   146,    82,   127,
     101,   128,    83,   129,    84
  };

  const unsigned char
  PDDLParser::yytable_[] =
  {
      56,    50,    52,    99,    91,    61,   102,    58,    74,    59,
      37,    39,    96,    63,   147,    75,   118,    95,    96,    97,
     150,    77,    61,    61,    57,    97,    47,    78,   140,   141,
      74,    48,    95,    96,   108,   141,    74,    75,    90,   124,
      97,     1,    61,    75,   105,   106,   138,   106,   107,   123,
     107,   139,    70,    90,    49,    90,   122,    99,     5,   107,
      32,    33,    34,    67,    68,    69,   117,    72,    68,    69,
      73,    80,    49,    69,    17,   135,     6,    69,    10,    11,
      33,    34,    54,    76,     7,    88,    69,    81,    98,    81,
     144,   145,   149,    12,    19,    15,    25,    60,    85,    20,
      18,    21,    26,    44,    28,    29,    30,   148,    43,    35,
      38,    40,    34,    45,    64,    54,   125,    49,    62,    65,
      81,    79,    86,    93,   131,    87,   100,   111,   136,    89,
      90,   103,   104,   110,   114,   142,   115,     0,   119,   116,
     120,   121,   126,   134,   130,   133,     0,   143,   137,   145,
      36,   151,     0,     0,    53
  };

  const short
  PDDLParser::yycheck_[] =
  {
      34,    32,    33,    82,    75,    41,    85,    37,    16,    39,
      22,    23,    16,    44,   140,    23,    14,    15,    16,    23,
     146,    55,    58,    59,    36,    23,    21,    57,    14,    15,
      16,    26,    15,    16,    21,    15,    16,    23,    25,   110,
      23,    20,    78,    23,    21,    22,    21,    22,    25,    21,
      25,    21,    21,    25,    23,    25,    22,   136,     3,    25,
       7,     8,     9,    21,    22,    23,    97,    21,    22,    23,
      21,    21,    23,    23,    23,    21,     0,    23,     4,     5,
       8,     9,    20,    21,    20,    22,    23,    20,    21,    20,
      21,    20,    21,    20,     6,    20,     4,    10,    19,    21,
      23,    20,    20,    17,    21,    21,    26,   141,    23,    20,
      20,    20,     9,    20,    18,    20,   110,    23,    21,    20,
      20,    23,    21,    11,    13,    23,    20,    12,   118,    25,
      25,    23,    25,    20,    20,   131,    95,    -1,    21,    23,
      21,    23,    20,    23,    21,    21,    -1,    21,    23,    20,
      22,    21,    -1,    -1,    33
  };

  const signed char
  PDDLParser::yystos_[] =
  {
       0,    20,    59,    60,    74,     3,     0,    20,    61,    75,
       4,     5,    20,    62,    63,    20,    76,    23,    23,     6,
      21,    20,    64,    65,    66,     4,    20,    77,    21,    21,
      26,    80,     7,     8,     9,    20,    65,    66,    20,    66,
      20,    67,    68,    23,    17,    20,    78,    21,    26,    23,
      81,    82,    81,    82,    20,    69,    89,    66,    67,    67,
      10,    68,    21,    81,    18,    20,    79,    21,    22,    23,
      21,    81,    21,    21,    16,    23,    21,    89,    67,    23,
      21,    20,    86,    90,    92,    19,    21,    23,    22,    25,
      25,    83,    84,    11,    70,    15,    16,    23,    21,    92,
      20,    88,    92,    23,    25,    21,    22,    25,    21,    83,
      20,    12,    71,    72,    20,    90,    23,    81,    14,    21,
      21,    23,    22,    21,    83,    84,    20,    87,    89,    91,
      21,    13,    73,    21,    23,    21,    86,    23,    21,    21,
      14,    15,    87,    21,    21,    20,    85,    91,    89,    21,
      91,    21
  };

  const signed char
  PDDLParser::yyr1_[] =
  {
       0,    58,    59,    59,    60,    61,    62,    62,    62,    62,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    69,
      69,    70,    70,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    84,    84,    85,    85,    86,    86,    87,    87,    88,
      88,    89,    89,    89,    90,    90,    91,    91,    92,    92
  };

  const signed char
  PDDLParser::yyr2_[] =
  {
       0,     2,     1,     1,     5,     4,     3,     4,     4,     5,
       4,     4,     4,     4,     4,     4,     1,     2,     6,     1,
       2,     4,     4,     3,     2,     2,     2,     8,     4,     4,
       4,     4,     4,     1,     2,     1,     2,     3,     4,     1,
       2,     3,     4,     1,     2,     1,     2,     1,     4,     1,
       4,     4,     4,     5,     4,     5,     1,     4,     1,     4
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const PDDLParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"define\"",
  "\"domain\"", "\"problem\"", "\"requirements\"", "\"types\"",
  "\"constants\"", "\"predicates\"", "\"action\"", "\"parameters\"",
  "\"preconditions\"", "\"effects\"", "\"and\"", "\"not\"", "\"=\"",
  "\"objects\"", "\"init\"", "\"goal\"", "\"(\"", "\")\"", "\"-\"",
  "\"name\"", "\"number\"", "\"variable\"", "\"requirekey\"",
  "\"domain-def\"", "\"domain-name\"", "\"domain-body\"",
  "\"problem-def\"", "\"problem-name\"", "\"domain-reference\"",
  "\"actions\"", "\"action-def\"", "\"action-def-body\"",
  "\"preconditions-list\"", "\"effects-list\"", "\"atomic-formula\"",
  "\"predicate\"", "\"grounded-predicate\"", "\"literal\"",
  "\"literal-list\"", "\"grounded-literal\"", "\"grounded-literal-list\"",
  "\"grounded-atomic-formula\"", "\"requirements-def\"",
  "\"requirekeys-list\"", "\"predicates-def\"", "\"predicates-list\"",
  "\"parameters-list\"", "\"typed-variables-list\"", "\"variables-list\"",
  "\"names-list\"", "\"typed-names-list\"", "\"objects-def\"",
  "\"init-def\"", "\"goal-def\"", "$accept", "pddl", "domain-def",
  "domain-name", "domain-body", "requirements-def", "types", "constants",
  "predicates-def", "actions", "action-def", "predicates-list",
  "parameters-list", "action-def-body", "preconditions-list",
  "effects-list", "problem-def", "problem-name", "domain-reference",
  "objects-def", "init-def", "goal-def", "requirekeys-list", "names-list",
  "typed-names-list", "variables-list", "typed-variables-list",
  "literal-list", "grounded-literal-list", "atomic-formula",
  "grounded-atomic-formula", "predicate", "grounded-predicate", "literal",
  "grounded-literal", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  PDDLParser::yyrline_[] =
  {
       0,   145,   145,   146,   149,   158,   161,   162,   163,   164,
     167,   170,   171,   175,   176,   179,   182,   183,   186,   193,
     194,   198,   206,   210,   216,   221,   223,   225,   233,   235,
     237,   239,   241,   244,   245,   249,   250,   254,   255,   259,
     260,   264,   272,   283,   284,   288,   289,   293,   294,   298,
     299,   303,   312,   317,   328,   333,   344,   345,   349,   350
  };

  void
  PDDLParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  PDDLParser::yy_reduce_print_ (int yyrule) const
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


} // yy
#line 2489 "src/pddlparser.tab.cc"

#line 354 "src/pddlparser.yy"



void
yy::PDDLParser::error (const location_type& l, const std::string& m)
{
    driver.error (l, m);
}

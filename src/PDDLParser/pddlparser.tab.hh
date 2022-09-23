// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file src/pddlparser.tab.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_SRC_PDDLPARSER_TAB_HH_INCLUDED
# define YY_YY_SRC_PDDLPARSER_TAB_HH_INCLUDED
// "%code requires" blocks.
#line 12 "src/pddlparser.yy"

#include <string>
#include <vector>
#include <tuple>

#include "domain.hh"
#include "problem.hh"
#include "action.hh"
#include "predicate.hh"

using StringList    = std::vector<std::string>;
using TypeDict      = std::map<std::string,std::string>;

using ActionList    = std::vector<Action*>;
using PredicateList = std::vector<Predicate*>;
using ParameterList = std::pair<StringList*,TypeDict*>;
using ArgumentList  = std::pair<StringList*,TypeDict*>;

using Literal       = std::pair<Predicate*,bool>;
using LiteralList   = std::vector<Literal*>;
using ActionDefBody = std::pair<LiteralList*,LiteralList*>;

using DomainBody    = struct {
    StringList     *requirements;
    PredicateList  *predicates;
    ActionList     *actions;
};


class PDDLDriver;

#line 81 "src/pddlparser.tab.hh"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace yy {
#line 221 "src/pddlparser.tab.hh"




  /// A Bison parser.
  class PDDLParser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // "action-def"
      // action-def
      char dummy1[sizeof (Action*)];

      // "action-def-body"
      // action-def-body
      char dummy2[sizeof (ActionDefBody*)];

      // "actions"
      // actions
      char dummy3[sizeof (ActionList*)];

      // "domain-def"
      // domain-def
      char dummy4[sizeof (Domain*)];

      // "domain-body"
      // domain-body
      char dummy5[sizeof (DomainBody*)];

      // "literal"
      // "grounded-literal"
      // literal
      // grounded-literal
      char dummy6[sizeof (Literal*)];

      // "preconditions-list"
      // "effects-list"
      // "atomic-formula"
      // "literal-list"
      // "grounded-literal-list"
      // "grounded-atomic-formula"
      // "init-def"
      // "goal-def"
      // preconditions-list
      // effects-list
      // init-def
      // goal-def
      // literal-list
      // grounded-literal-list
      // atomic-formula
      // grounded-atomic-formula
      char dummy7[sizeof (LiteralList*)];

      // "parameters-list"
      // parameters-list
      char dummy8[sizeof (ParameterList*)];

      // "predicate"
      // "grounded-predicate"
      // predicate
      // grounded-predicate
      char dummy9[sizeof (Predicate*)];

      // "predicates-def"
      // "predicates-list"
      // predicates-def
      // predicates-list
      char dummy10[sizeof (PredicateList*)];

      // "problem-def"
      // problem-def
      char dummy11[sizeof (Problem*)];

      // "requirements-def"
      // "requirekeys-list"
      // "variables-list"
      // "names-list"
      // "objects-def"
      // requirements-def
      // objects-def
      // requirekeys-list
      // names-list
      // variables-list
      char dummy12[sizeof (StringList*)];

      // "typed-variables-list"
      // "typed-names-list"
      // typed-names-list
      // typed-variables-list
      char dummy13[sizeof (TypeDict*)];

      // "number"
      char dummy14[sizeof (int)];

      // "name"
      // "variable"
      // "requirekey"
      // "domain-name"
      // "problem-name"
      // "domain-reference"
      // domain-name
      // problem-name
      // domain-reference
      char dummy15[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOK_YYEMPTY = -2,
    TOK_END = 0,                   // "end of file"
    TOK_YYerror = 256,             // error
    TOK_YYUNDEF = 257,             // "invalid token"
    TOK_DEFINE = 258,              // "define"
    TOK_DOMAIN = 259,              // "domain"
    TOK_PROBLEM = 260,             // "problem"
    TOK_REQUIREMENTS = 261,        // "requirements"
    TOK_TYPES = 262,               // "types"
    TOK_CONSTANTS = 263,           // "constants"
    TOK_PREDICATES = 264,          // "predicates"
    TOK_ACTION = 265,              // "action"
    TOK_PARAMETERS = 266,          // "parameters"
    TOK_PRECONDITIONS = 267,       // "preconditions"
    TOK_EFFECTS = 268,             // "effects"
    TOK_AND = 269,                 // "and"
    TOK_NOT = 270,                 // "not"
    TOK_EQUAL = 271,               // "="
    TOK_OBJECTS = 272,             // "objects"
    TOK_INIT = 273,                // "init"
    TOK_GOAL = 274,                // "goal"
    TOK_LPAREN = 275,              // "("
    TOK_RPAREN = 276,              // ")"
    TOK_HYPHEN = 277,              // "-"
    TOK_NAME = 278,                // "name"
    TOK_NUMBER = 279,              // "number"
    TOK_VARIABLE = 280,            // "variable"
    TOK_REQUIREKEY = 281           // "requirekey"
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 58, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_DEFINE = 3,                            // "define"
        S_DOMAIN = 4,                            // "domain"
        S_PROBLEM = 5,                           // "problem"
        S_REQUIREMENTS = 6,                      // "requirements"
        S_TYPES = 7,                             // "types"
        S_CONSTANTS = 8,                         // "constants"
        S_PREDICATES = 9,                        // "predicates"
        S_ACTION = 10,                           // "action"
        S_PARAMETERS = 11,                       // "parameters"
        S_PRECONDITIONS = 12,                    // "preconditions"
        S_EFFECTS = 13,                          // "effects"
        S_AND = 14,                              // "and"
        S_NOT = 15,                              // "not"
        S_EQUAL = 16,                            // "="
        S_OBJECTS = 17,                          // "objects"
        S_INIT = 18,                             // "init"
        S_GOAL = 19,                             // "goal"
        S_LPAREN = 20,                           // "("
        S_RPAREN = 21,                           // ")"
        S_HYPHEN = 22,                           // "-"
        S_NAME = 23,                             // "name"
        S_NUMBER = 24,                           // "number"
        S_VARIABLE = 25,                         // "variable"
        S_REQUIREKEY = 26,                       // "requirekey"
        S_27_domain_def_ = 27,                   // "domain-def"
        S_28_domain_name_ = 28,                  // "domain-name"
        S_29_domain_body_ = 29,                  // "domain-body"
        S_30_problem_def_ = 30,                  // "problem-def"
        S_31_problem_name_ = 31,                 // "problem-name"
        S_32_domain_reference_ = 32,             // "domain-reference"
        S_33_actions_ = 33,                      // "actions"
        S_34_action_def_ = 34,                   // "action-def"
        S_35_action_def_body_ = 35,              // "action-def-body"
        S_36_preconditions_list_ = 36,           // "preconditions-list"
        S_37_effects_list_ = 37,                 // "effects-list"
        S_38_atomic_formula_ = 38,               // "atomic-formula"
        S_39_predicate_ = 39,                    // "predicate"
        S_40_grounded_predicate_ = 40,           // "grounded-predicate"
        S_41_literal_ = 41,                      // "literal"
        S_42_literal_list_ = 42,                 // "literal-list"
        S_43_grounded_literal_ = 43,             // "grounded-literal"
        S_44_grounded_literal_list_ = 44,        // "grounded-literal-list"
        S_45_grounded_atomic_formula_ = 45,      // "grounded-atomic-formula"
        S_46_requirements_def_ = 46,             // "requirements-def"
        S_47_requirekeys_list_ = 47,             // "requirekeys-list"
        S_48_predicates_def_ = 48,               // "predicates-def"
        S_49_predicates_list_ = 49,              // "predicates-list"
        S_50_parameters_list_ = 50,              // "parameters-list"
        S_51_typed_variables_list_ = 51,         // "typed-variables-list"
        S_52_variables_list_ = 52,               // "variables-list"
        S_53_names_list_ = 53,                   // "names-list"
        S_54_typed_names_list_ = 54,             // "typed-names-list"
        S_55_objects_def_ = 55,                  // "objects-def"
        S_56_init_def_ = 56,                     // "init-def"
        S_57_goal_def_ = 57,                     // "goal-def"
        S_YYACCEPT = 58,                         // $accept
        S_pddl = 59,                             // pddl
        S_60_domain_def = 60,                    // domain-def
        S_61_domain_name = 61,                   // domain-name
        S_62_domain_body = 62,                   // domain-body
        S_63_requirements_def = 63,              // requirements-def
        S_types = 64,                            // types
        S_constants = 65,                        // constants
        S_66_predicates_def = 66,                // predicates-def
        S_actions = 67,                          // actions
        S_68_action_def = 68,                    // action-def
        S_69_predicates_list = 69,               // predicates-list
        S_70_parameters_list = 70,               // parameters-list
        S_71_action_def_body = 71,               // action-def-body
        S_72_preconditions_list = 72,            // preconditions-list
        S_73_effects_list = 73,                  // effects-list
        S_74_problem_def = 74,                   // problem-def
        S_75_problem_name = 75,                  // problem-name
        S_76_domain_reference = 76,              // domain-reference
        S_77_objects_def = 77,                   // objects-def
        S_78_init_def = 78,                      // init-def
        S_79_goal_def = 79,                      // goal-def
        S_80_requirekeys_list = 80,              // requirekeys-list
        S_81_names_list = 81,                    // names-list
        S_82_typed_names_list = 82,              // typed-names-list
        S_83_variables_list = 83,                // variables-list
        S_84_typed_variables_list = 84,          // typed-variables-list
        S_85_literal_list = 85,                  // literal-list
        S_86_grounded_literal_list = 86,         // grounded-literal-list
        S_87_atomic_formula = 87,                // atomic-formula
        S_88_grounded_atomic_formula = 88,       // grounded-atomic-formula
        S_predicate = 89,                        // predicate
        S_90_grounded_predicate = 90,            // grounded-predicate
        S_literal = 91,                          // literal
        S_92_grounded_literal = 92               // grounded-literal
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        value.move< Action* > (std::move (that.value));
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        value.move< ActionDefBody* > (std::move (that.value));
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        value.move< ActionList* > (std::move (that.value));
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        value.move< Domain* > (std::move (that.value));
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        value.move< DomainBody* > (std::move (that.value));
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        value.move< Literal* > (std::move (that.value));
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
        value.move< LiteralList* > (std::move (that.value));
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        value.move< ParameterList* > (std::move (that.value));
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        value.move< Predicate* > (std::move (that.value));
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        value.move< PredicateList* > (std::move (that.value));
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        value.move< Problem* > (std::move (that.value));
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
        value.move< StringList* > (std::move (that.value));
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        value.move< TypeDict* > (std::move (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (std::move (that.value));
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
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Action*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Action*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ActionDefBody*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ActionDefBody*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ActionList*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ActionList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Domain*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Domain*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DomainBody*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DomainBody*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Literal*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Literal*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, LiteralList*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const LiteralList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ParameterList*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ParameterList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Predicate*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Predicate*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, PredicateList*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const PredicateList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Problem*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Problem*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, StringList*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const StringList*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TypeDict*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TypeDict*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        value.template destroy< Action* > ();
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        value.template destroy< ActionDefBody* > ();
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        value.template destroy< ActionList* > ();
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        value.template destroy< Domain* > ();
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        value.template destroy< DomainBody* > ();
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        value.template destroy< Literal* > ();
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
        value.template destroy< LiteralList* > ();
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        value.template destroy< ParameterList* > ();
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        value.template destroy< Predicate* > ();
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        value.template destroy< PredicateList* > ();
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        value.template destroy< Problem* > ();
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
        value.template destroy< StringList* > ();
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        value.template destroy< TypeDict* > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.template destroy< int > ();
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
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return PDDLParser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_END
                   || (token::TOK_YYerror <= tok && tok <= token::TOK_HYPHEN));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Action* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const Action*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 289);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, ActionDefBody* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const ActionDefBody*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 290);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, ActionList* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const ActionList*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 288);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Domain* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const Domain*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 282);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, DomainBody* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const DomainBody*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 284);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Literal* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const Literal*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 296
                   || tok == 298);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, LiteralList* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const LiteralList*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT ((291 <= tok && tok <= 293)
                   || tok == 297
                   || (299 <= tok && tok <= 300)
                   || (311 <= tok && tok <= 312));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, ParameterList* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const ParameterList*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 305);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Predicate* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const Predicate*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT ((294 <= tok && tok <= 295));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, PredicateList* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const PredicateList*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT ((303 <= tok && tok <= 304));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Problem* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const Problem*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 285);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, StringList* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const StringList*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT ((301 <= tok && tok <= 302)
                   || (307 <= tok && tok <= 308)
                   || tok == 310);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, TypeDict* v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const TypeDict*& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == 306
                   || tok == 309);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_NUMBER);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_NAME
                   || (token::TOK_VARIABLE <= tok && tok <= token::TOK_REQUIREKEY)
                   || tok == 283
                   || (286 <= tok && tok <= 287));
#endif
      }
    };

    /// Build a parser object.
    PDDLParser (PDDLDriver& driver_yyarg);
    virtual ~PDDLParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    PDDLParser (const PDDLParser&) = delete;
    /// Non copyable.
    PDDLParser& operator= (const PDDLParser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::TOK_END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::TOK_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::TOK_YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::TOK_YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::TOK_YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::TOK_YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFINE (location_type l)
      {
        return symbol_type (token::TOK_DEFINE, std::move (l));
      }
#else
      static
      symbol_type
      make_DEFINE (const location_type& l)
      {
        return symbol_type (token::TOK_DEFINE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOMAIN (location_type l)
      {
        return symbol_type (token::TOK_DOMAIN, std::move (l));
      }
#else
      static
      symbol_type
      make_DOMAIN (const location_type& l)
      {
        return symbol_type (token::TOK_DOMAIN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PROBLEM (location_type l)
      {
        return symbol_type (token::TOK_PROBLEM, std::move (l));
      }
#else
      static
      symbol_type
      make_PROBLEM (const location_type& l)
      {
        return symbol_type (token::TOK_PROBLEM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REQUIREMENTS (location_type l)
      {
        return symbol_type (token::TOK_REQUIREMENTS, std::move (l));
      }
#else
      static
      symbol_type
      make_REQUIREMENTS (const location_type& l)
      {
        return symbol_type (token::TOK_REQUIREMENTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPES (location_type l)
      {
        return symbol_type (token::TOK_TYPES, std::move (l));
      }
#else
      static
      symbol_type
      make_TYPES (const location_type& l)
      {
        return symbol_type (token::TOK_TYPES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONSTANTS (location_type l)
      {
        return symbol_type (token::TOK_CONSTANTS, std::move (l));
      }
#else
      static
      symbol_type
      make_CONSTANTS (const location_type& l)
      {
        return symbol_type (token::TOK_CONSTANTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREDICATES (location_type l)
      {
        return symbol_type (token::TOK_PREDICATES, std::move (l));
      }
#else
      static
      symbol_type
      make_PREDICATES (const location_type& l)
      {
        return symbol_type (token::TOK_PREDICATES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ACTION (location_type l)
      {
        return symbol_type (token::TOK_ACTION, std::move (l));
      }
#else
      static
      symbol_type
      make_ACTION (const location_type& l)
      {
        return symbol_type (token::TOK_ACTION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PARAMETERS (location_type l)
      {
        return symbol_type (token::TOK_PARAMETERS, std::move (l));
      }
#else
      static
      symbol_type
      make_PARAMETERS (const location_type& l)
      {
        return symbol_type (token::TOK_PARAMETERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PRECONDITIONS (location_type l)
      {
        return symbol_type (token::TOK_PRECONDITIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_PRECONDITIONS (const location_type& l)
      {
        return symbol_type (token::TOK_PRECONDITIONS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EFFECTS (location_type l)
      {
        return symbol_type (token::TOK_EFFECTS, std::move (l));
      }
#else
      static
      symbol_type
      make_EFFECTS (const location_type& l)
      {
        return symbol_type (token::TOK_EFFECTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (location_type l)
      {
        return symbol_type (token::TOK_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const location_type& l)
      {
        return symbol_type (token::TOK_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (location_type l)
      {
        return symbol_type (token::TOK_NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const location_type& l)
      {
        return symbol_type (token::TOK_NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (location_type l)
      {
        return symbol_type (token::TOK_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const location_type& l)
      {
        return symbol_type (token::TOK_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OBJECTS (location_type l)
      {
        return symbol_type (token::TOK_OBJECTS, std::move (l));
      }
#else
      static
      symbol_type
      make_OBJECTS (const location_type& l)
      {
        return symbol_type (token::TOK_OBJECTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INIT (location_type l)
      {
        return symbol_type (token::TOK_INIT, std::move (l));
      }
#else
      static
      symbol_type
      make_INIT (const location_type& l)
      {
        return symbol_type (token::TOK_INIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GOAL (location_type l)
      {
        return symbol_type (token::TOK_GOAL, std::move (l));
      }
#else
      static
      symbol_type
      make_GOAL (const location_type& l)
      {
        return symbol_type (token::TOK_GOAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (location_type l)
      {
        return symbol_type (token::TOK_LPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const location_type& l)
      {
        return symbol_type (token::TOK_LPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (location_type l)
      {
        return symbol_type (token::TOK_RPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const location_type& l)
      {
        return symbol_type (token::TOK_RPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HYPHEN (location_type l)
      {
        return symbol_type (token::TOK_HYPHEN, std::move (l));
      }
#else
      static
      symbol_type
      make_HYPHEN (const location_type& l)
      {
        return symbol_type (token::TOK_HYPHEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NAME (std::string v, location_type l)
      {
        return symbol_type (token::TOK_NAME, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NAME (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_NAME, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NUMBER (int v, location_type l)
      {
        return symbol_type (token::TOK_NUMBER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NUMBER (const int& v, const location_type& l)
      {
        return symbol_type (token::TOK_NUMBER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VARIABLE (std::string v, location_type l)
      {
        return symbol_type (token::TOK_VARIABLE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_VARIABLE (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_VARIABLE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REQUIREKEY (std::string v, location_type l)
      {
        return symbol_type (token::TOK_REQUIREKEY, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_REQUIREKEY (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_REQUIREKEY, v, l);
      }
#endif


    class context
    {
    public:
      context (const PDDLParser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const PDDLParser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    PDDLParser (const PDDLParser&);
    /// Non copyable.
    PDDLParser& operator= (const PDDLParser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 154,     ///< Last index in yytable_.
      yynnts_ = 35,  ///< Number of nonterminal symbols.
      yyfinal_ = 6 ///< Termination state number.
    };


    // User arguments.
    PDDLDriver& driver;

  };

  inline
  PDDLParser::symbol_kind_type
  PDDLParser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
    };
    // Last valid token kind.
    const int code_max = 312;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  PDDLParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        value.copy< Action* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        value.copy< ActionDefBody* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        value.copy< ActionList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        value.copy< Domain* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        value.copy< DomainBody* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        value.copy< Literal* > (YY_MOVE (that.value));
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
        value.copy< LiteralList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        value.copy< ParameterList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        value.copy< Predicate* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        value.copy< PredicateList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        value.copy< Problem* > (YY_MOVE (that.value));
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
        value.copy< StringList* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        value.copy< TypeDict* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< int > (YY_MOVE (that.value));
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
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  PDDLParser::symbol_kind_type
  PDDLParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  PDDLParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  PDDLParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_34_action_def_: // "action-def"
      case symbol_kind::S_68_action_def: // action-def
        value.move< Action* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_35_action_def_body_: // "action-def-body"
      case symbol_kind::S_71_action_def_body: // action-def-body
        value.move< ActionDefBody* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_33_actions_: // "actions"
      case symbol_kind::S_actions: // actions
        value.move< ActionList* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_27_domain_def_: // "domain-def"
      case symbol_kind::S_60_domain_def: // domain-def
        value.move< Domain* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_29_domain_body_: // "domain-body"
      case symbol_kind::S_62_domain_body: // domain-body
        value.move< DomainBody* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_41_literal_: // "literal"
      case symbol_kind::S_43_grounded_literal_: // "grounded-literal"
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_92_grounded_literal: // grounded-literal
        value.move< Literal* > (YY_MOVE (s.value));
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
        value.move< LiteralList* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_50_parameters_list_: // "parameters-list"
      case symbol_kind::S_70_parameters_list: // parameters-list
        value.move< ParameterList* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_39_predicate_: // "predicate"
      case symbol_kind::S_40_grounded_predicate_: // "grounded-predicate"
      case symbol_kind::S_predicate: // predicate
      case symbol_kind::S_90_grounded_predicate: // grounded-predicate
        value.move< Predicate* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_48_predicates_def_: // "predicates-def"
      case symbol_kind::S_49_predicates_list_: // "predicates-list"
      case symbol_kind::S_66_predicates_def: // predicates-def
      case symbol_kind::S_69_predicates_list: // predicates-list
        value.move< PredicateList* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_30_problem_def_: // "problem-def"
      case symbol_kind::S_74_problem_def: // problem-def
        value.move< Problem* > (YY_MOVE (s.value));
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
        value.move< StringList* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_51_typed_variables_list_: // "typed-variables-list"
      case symbol_kind::S_54_typed_names_list_: // "typed-names-list"
      case symbol_kind::S_82_typed_names_list: // typed-names-list
      case symbol_kind::S_84_typed_variables_list: // typed-variables-list
        value.move< TypeDict* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (YY_MOVE (s.value));
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
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  PDDLParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  PDDLParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  PDDLParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  PDDLParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  PDDLParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  PDDLParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  PDDLParser::symbol_kind_type
  PDDLParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  PDDLParser::symbol_kind_type
  PDDLParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


} // yy
#line 2704 "src/pddlparser.tab.hh"




#endif // !YY_YY_SRC_PDDLPARSER_TAB_HH_INCLUDED

#ifndef _CSDBG_PARSER
#define _CSDBG_PARSER 1

/**
	@file include/parser.hpp

	@brief Class csdbg::parser definition
*/

#include "./dictionary.hpp"
#include "./style.hpp"

namespace csdbg {

/**
	@brief Stack trace parser and syntax highlighter for VT100 terminals

	A parser object can be used to parse stack traces produced by libcsdbg or any
	text of arbitrary syntax. It is easy to define the parser syntax using POSIX
	extended regular expressions. Parsed text can then be highlighted for VT100
	terminals (XTerm, RXVT, GNOME terminal e.t.c), using configurable styles for
	each type of token. Token types can be identified using a set of C++ language
	dictionaries. By subclassing class csdbg::parser, users can create parsers and
	higlighters for any kind of content, syntax and output media

	@see csdbg::g_trace_syntax
	@see <a href="index.html#sec5_7"><b>5.7 Using the stack trace parser (syntax highlighter)</b></a>
*/
class parser: virtual public string
{
protected:

	/* Protected static variables */

	static parser *m_default;							/**< @brief Default parser */

	static style *m_fallback;							/**< @brief Shared fallback style */


	/* Protected variables */

	chain<dictionary> *m_dictionaries;		/**< @brief Dictionary collection */

	chain<style> *m_styles;								/**< @brief VT100 style collection */


	/* Protected static methods */

	static void on_lib_load() __attribute((constructor));

	static void on_lib_unload()	__attribute((destructor));

public:

	/* Friend classes and functions */

	friend std::ostream& operator<<(std::ostream&, const parser&);


	/* Constructors, copy constructors and destructor */

	parser();

	parser(const parser&);

	virtual	~parser();

	virtual parser* clone() const;


	/* Accessor methods */

	static parser* get_default();

	static style* get_fallback_style();


	/* Operator overloading methods */

	virtual parser& operator=(const parser&);


	/* Generic methods */

	/* Dictionary handling methods */

	virtual dictionary* add_dictionary(const i8*, const i8*, bool);

	virtual parser& add_dictionary(dictionary*);

	virtual parser& remove_dictionary(const i8*);

	virtual parser& remove_all_dictionaries();

	virtual dictionary* get_dictionary(const i8*) const;

	virtual chain<string>* get_dictionary_names() const;


	/* Style handling methods */

	virtual style* add_style(const i8*, color_t, color_t, attrset_t);

	virtual parser& add_style(style*);

	virtual parser& remove_style(const i8*);

	virtual parser& remove_all_styles();

	virtual style* get_style(const i8*) const;

	virtual chain<string>* get_style_names() const;


	/* Parse/highlight/lookup methods */

	virtual chain<string>* parse(const i8* = NULL, bool = false) const;

	virtual string* highlight(const i8* = NULL, bool = false) const;

	virtual bool lookup(const string&, const i8*, bool = false) const;

	virtual const i8* lookup(const string&, bool = false) const;
};

}

#endif


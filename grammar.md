
-------------------------------------------------------------------------------
shell grammar
-------------------------------------------------------------------------------


program:
	linebreak complete_commands linebreak | linebreak;
complete_commands:
		complete_commands newline_list complete_command
		| complete_command;
complete_command:
		list separator_op | list;
list:
		list separator_op and_or | and_or;
and_or:
		pipeline
		| and_or AND_IF linebreak pipeline
		| and_or OR_IF linebreak pipeline;
pipeline:
		pipe_sequence | Bang pipe_sequence;
pipe_sequence:
		command | pipe_sequence '|'linebreak command;
command:
		simple_command | compound_command
		| compound_command redirect_list | function_definition;
compound_command:
		brace_group | subshell | for_clause | case_clause
		| if_clause | while_clause | until_clause;
subshell:
		'('compound_list ')';
compound_list:
		linebreak term | linebreak term separator;
term:
		term separator and_or | and_or;
while_clause:
		While compound_list do_group;
do_group:
		Do compound_list Done /* Apply rule 6 */;
simple_command:
		cmd_prefix cmd_word cmd_suffix
		| cmd_prefix cmd_word
		| cmd_prefix
		| cmd_name cmd_suffix
		| cmd_name;
cmd_name:
		WORD /* Apply rule 7a */;
cmd_word:
		WORD /* Apply rule 7b */;
newline_list:
		NEWLINE | newline_list NEWLINE;
linebreak:
		newline_list | /* empty */;
separator_op:
		'&'| ';';
separator:
		separator_op linebreak | newline_list;
sequential_sep:
';'linebreak | newline_list;

 // The rules for the following nonterminals are elided:
 // for_clause , name , in, wordlist , case_clause ,
 // case_list_ns , case_list , case_item_ns , case_item ,
 // pattern if_clause , else_part , until_clause ,
 // function_definition , function_body , fname ,
 // brace_group , cmd_prefix , cmd_suffix , redirect_list ,
 // io_redirect , io_file , filename , io_here and here_end


-------------------------------------------------------------------------------
 Other grammar :
-------------------------------------------------------------------------------
 <cmdline>	::= <block>
		| 		<block> (";" | "&") <cmdline>  

<block>		::= <pipeline> {("&&" | "||") <pipeline>}

<pipeline>	::= <command> {"|" <command>}

<command>	::= <cmdlist>
				| "(" <cmdline> ")" <redir>	(* subshell *)

<cmdlist>	::= <redir>+			(* at least one redirect - without WORDs *)
				| <redir> {<arg> <redir>}+	(* at least one WORD - zero or more <redir> in any place *)

<redir>		::= {("<" | "<<" | ">" | ">>") <filename>}	(* a delimiter in case of heredoc *)

<arg>		::= token WORD | token VAR | token GROUP

<filename>	::= token WORD | token VAR | token GROUP


-------------------------------------------------------------------------------
 Other grammar : sh61
-------------------------------------------------------------------------------
commandline ::= list
          |  list ";"
          |  list "&"

list     ::=  conditional
          |   list ";" conditional
          |   list "&" conditional

conditional ::=  pipeline
          |   conditional "&&" pipeline
          |   conditional "||" pipeline

pipeline ::=  command
          |   pipeline "|" command

command  ::=  word
          |   redirection
          |   command word
          |   command redirection

redirection  ::=  redirectionop filename
redirectionop  ::=  "<"  |  ">"  |  "2>"




-------------------------------------------------------------------------------
Syntax Rules
-------------------------------------------------------------------------------

- UNEXPECTED TOKENS:
	- `;;' (this token is always unrecognized in bash and zsh shells)

* AND, OR, PIPE, FG, BG:
	- left: [WSPACE] (STRING | CPAR)
	- right: [WSPACE] (STRING | REDIRECT | OPAR | if <FG, BG> ENDOFCMD)

* OPAR "(":
	- left: CMDBEGIN | [WSPACE] (AND | OR | PIPE | OPAR)
	- right: [WSPACE] (STRING | REDIRECT | OPAR)

* CPAR ")":
	- left: [WSPACE] (STRING | CPAR)
	- right: [WSPACE] (AND | OR | PIPE | CPAR | ENDOFCMD)

* REDIRECT:
	- right: [WSPACE] STRING

* PARENTHESES MATCHING AND QUOTING:
	- inside each pair parentheses should not be an empthy command.
	- every open parentheses has to have a matching closing parentheses.
	- every single/double quote have to be closed.

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:50:38 by obeaj             #+#    #+#             */
/*   Updated: 2022/04/16 17:52:26 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AST_H
# define AST_H

/*** DATA ***/

typedef enum e_asttype{
	AST_PIPE =		(1 << 0),
	AST_SC =		(1 << 1),
	AST_AND =		(1 << 2),
	AST_OR =		(1 << 3),
	AST_REDIR =		(1 << 4),
	AST_GTH	 =		(1 << 5),
	AST_GGTH =		(1 << 6),
	AST_LTH =		(1 << 7),
	AST_HDOC =		(1 << 8),
	AST_EXEC =		(1 << 9),
	AST_ARG =		(1 << 10),
	AST_DATA =		(1 << 11),
	AST_BG =		(1 << 12),
	AST_SUB = 		(1 << 13)
}	t_asttype;

typedef struct s_ast	t_ast;

struct s_ast {
	int		type;
	char	*data;
	t_ast	*left;
	t_ast	*right;
};

/*** PROTOTYPES ***/

/* ast_utils_1.c */
int		ast_gettype(t_ast *ast);
void	ast_del(t_ast *ast);
void	ast_attach(t_ast *root, t_ast *left, t_ast *right);
void	ast_settype(t_ast *ast, t_asttype type);
void	ast_setdata(t_ast *ast, char *data);

/* ast_utils_2.c */
void	ast_insert(t_ast *root, t_ast *node, bool on_right);
void	ast_insert_and_or(t_ast **root, t_ast *new_root, bool last);

#endif

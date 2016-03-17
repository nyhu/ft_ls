/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr_acl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 10:24:09 by tboos             #+#    #+#             */
/*   Updated: 2016/03/17 10:56:40 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_returnacl(char *name)
{
	acl_t	acl;

	if ((acl = acl_get_file(name, ACL_TYPE_EXTENDED)))
	{
		acl_free((void *)acl);
		return ('+');
	}
	else if ((listxattr(name, NULL, 0, XATTR_NOFOLLOW)) > 0)
		return ('@');
	return (' ');
}

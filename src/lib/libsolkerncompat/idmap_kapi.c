/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*
 * Windows to Solaris Identity Mapping kernel API
 * This module provides an API to map Windows SIDs to
 * Solaris UID and GIDs.
 */


#include <sys/types.h>
#ifdef	DEBUG
#include <sys/cmn_err.h>
#endif	/* DEBUG */
#include <sys/proc.h>
#include <sys/sunddi.h>
#include <sys/param.h>
#include <sys/atomic.h>
#include <sys/sysmacros.h>
#include <sys/disp.h>
#include <sys/kidmap.h>


/*
 * Defined types
 */

/*
 * Given Domain SID and RID, get UID
 *
 * Input:
 * sid_prefix	- Domain SID in canonical form
 * rid	- RID
 *
 * Output:
 * uid  - POSIX UID if return == IDMAP_SUCCESS
 *
 * Return:
 * Success return IDMAP_SUCCESS else IDMAP error
 */
idmap_stat
kidmap_getuidbysid(zone_t *zone, const char *sid_prefix, uint32_t rid,
		uid_t *uid)
{
	idmap_stat		status;

	/* Door call not implemented */
	*uid = UID_NOBODY;
	status = IDMAP_ERR_NOMAPPING;
	
	return (status);
}


/*
 * Given Domain SID and RID, get GID
 *
 * Input:
 * sid_prefix	- Domain SID in canonical form
 * rid	- RID
 *
 * Output:
 * gid  - POSIX UID if return == IDMAP_SUCCESS
 *
 * Return:
 * Success return IDMAP_SUCCESS else IDMAP error
 */
idmap_stat
kidmap_getgidbysid(zone_t *zone, const char *sid_prefix, uint32_t rid,
		gid_t *gid)
{
	idmap_stat		status;

	/* Door call not implemented */
	status = IDMAP_ERR_NOMAPPING;
	*gid = GID_NOBODY;

	return (status);
}


/*
 * Given UID, get Domain SID and RID
 *
 * Input:
 * uid - Posix UID
 *
 * Output:
 * sid_prefix	- Domain SID if return == IDMAP_SUCCESS
 * rid	- RID if return == IDMAP_SUCCESS
 *
 * Return:
 * Success return IDMAP_SUCCESS else IDMAP error
 */
idmap_stat
kidmap_getsidbyuid(zone_t *zone, uid_t uid, const char **sid_prefix,
		uint32_t *rid)
{
	idmap_stat		status;
	
	/* Door call not implemented */
	status = IDMAP_ERR_NOMAPPING;
	*rid = 0;
	*sid_prefix = NULL;

	return (status);
}


/*
 * Given GID, get Domain SID and RID
 *
 * Input:
 * gid - Posix GID
 *
 * Output:
 * sid_prefix	- Domain SID if return == IDMAP_SUCCESS
 * rid	- RID if return == IDMAP_SUCCESS
 *
 * Return:
 * Success return IDMAP_SUCCESS else IDMAP error
 */
idmap_stat
kidmap_getsidbygid(zone_t *zone, gid_t gid, const char **sid_prefix,
		uint32_t *rid)
{
	idmap_stat		status;

	/* Door call not implemented */
	status = IDMAP_ERR_NOMAPPING;
	*rid = 0;
	*sid_prefix = NULL;

	return (status);
}

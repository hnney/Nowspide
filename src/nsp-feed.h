/*
 * Copyright © 2009-2010 Siyan Panayotov <xsisqox@gmail.com>
 *
 * This file is part of Nowspide.
 *
 * Nowspide is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nowspide is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nowspide.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __NSP_FEED_H_
#define __NSP_FEED_H_ 1

#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "nsp-db.h"
#include "nsp-net.h"
#include "nsp-typedefs.h"
#include "nsp-feed-item.h"

typedef enum {
	NSP_FEED_UNKNOWN,
	NSP_FEED_RSS_0_9,
	NSP_FEED_RSS_1_0,
	NSP_FEED_RSS_2_0,
	NSP_FEED_ATOM_0_3,
	NSP_FEED_ATOM_1_0
} NspFeedType;

typedef struct _NspFeed NspFeed;

struct _NspFeed
{
	NspFeedType type;
	int id;
	char *title;
	char *url;
	char *site_url;
	char *description;
	GList * items;
	int unread_items;
	GtkTreeStore *items_store;
	GtkTreeModel *items_sorter;
	GMutex *mutex;
	GdkPixbuf *icon;
};

NspFeed * nsp_feed_new();
NspFeed * nsp_feed_new_from_url(const char *xml);

GtkTreeModel *nsp_feed_get_items_model(NspFeed *feed);

int nsp_feed_load_items_from_db(NspFeed *feed);
GList * nsp_feed_load_feeds_from_db();
GList * nsp_feed_load_feeds_with_items_from_db();

int nsp_feed_save_to_db(NspFeed *feed);

int nsp_feed_update_items(NspFeed *feed);
void nsp_feed_update_unread_count(NspFeed *feed);
void nsp_feed_update_model(NspFeed *feed);
int nsp_feed_update_icon(NspFeed *feed);

void nsp_feed_read_all(NspFeed *feed);
int nsp_feed_delete(NspFeed *feed);

int nsp_feed_delete_item(NspFeed *feed, NspFeedItem *feed_item);

int nsp_feed_clear_items(NspFeed *feed);
void	nsp_feed_free 		(NspFeed *feed);

#endif /* __NSP_FEED_H_ */

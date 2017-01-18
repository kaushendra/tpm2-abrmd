#ifndef HANDLE_MAP_H
#define HANDLE_MAP_H

#include <glib.h>
#include <glib-object.h>
#include <pthread.h>
#include <sapi/tpm20.h>

#include "handle-map-entry.h"

G_BEGIN_DECLS

typedef struct _HandleMapClass {
    GObjectClass      parent;
} HandleMapClass;

typedef struct _HandleMap {
    GObject             parent_instance;
    pthread_mutex_t     mutex;
    TPM_HT              handle_type;
    TPM_HANDLE          handle_count;
    GHashTable         *phandle_to_entry_table;
    GHashTable         *vhandle_to_entry_table;
} HandleMap;

#define TYPE_HANDLE_MAP              (handle_map_get_type   ())
#define HANDLE_MAP(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj),   TYPE_HANDLE_MAP, HandleMap))
#define HANDLE_MAP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST    ((klass), TYPE_HANDLE_MAP, HandleMapClass))
#define IS_HANDLE_MAP(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   TYPE_HANDLE_MAP))
#define IS_HANDLE_MAP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE    ((klass), TYPE_HANDLE_MAP))
#define HANDLE_MAP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS  ((obj),   TYPE_HANDLE_MAP, HandleMapClass))

GType            handle_map_get_type    (void);
HandleMap*       handle_map_new         (TPM_HT          handle_type);
void             handle_map_insert      (HandleMap      *map,
                                         TPM_HANDLE      phandle,
                                         TPM_HANDLE      vhandle,
                                         HandleMapEntry *entry);
gint             handle_map_premove     (HandleMap     *map,
                                         TPM_HANDLE     phandle);
gint             handle_map_vremove     (HandleMap     *map,
                                         TPM_HANDLE     vremove);
HandleMapEntry*  handle_map_plookup     (HandleMap     *map,
                                         TPM_HANDLE     phandle);
HandleMapEntry*  handle_map_vlookup     (HandleMap     *map,
                                         TPM_HANDLE     vhandle);
guint            handle_map_size        (HandleMap     *map);
TPM_HANDLE       handle_map_next_vhandle (HandleMap    *map);

G_END_DECLS
#endif /* HANDLE_MAP_H */
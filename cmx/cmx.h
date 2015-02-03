
#ifndef CMX_H
#define CMX_H 1

#include <cmx/cmx-token.h>
#include <cmx/cmx-meta-body.h>
#include <cmx/cmx-synchronize.h>
#include <cmx/cmx-struct-refs.h>
#include <cmx/cmx-struct-shareable.h>
#include <cmx/cmx-env-glib.h>

#define CMX_BUILD_VERSION(Major, Minor, Patch)                          \
    ((Major * 1000 + Minor) * 1000 + Patch)

#define CMX_VERSION CMX_BUILD_VERSION (1, 0, 0)

#endif

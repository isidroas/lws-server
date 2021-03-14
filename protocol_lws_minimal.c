#if !defined (LWS_PLUGIN_STATIC)
#define LWS_DLL
#define LWS_INTERNAL
#include <libwebsockets.h>
#endif

#include <string.h>

static int
callback_minimal(struct lws *wsi, enum lws_callback_reasons reason,
			void *user, void *in, size_t len)
{
	int m;

	switch (reason) {

	case LWS_CALLBACK_RECEIVE:

        lwsl_user("msg received: %.*s\n",(int)len,(char *) in);

        char *cadena="OK";
        char *cadena_ext[50];
		memcpy((char *)cadena_ext + LWS_PRE, cadena, 3);
		m = lws_write(wsi, ((unsigned char *)cadena_ext) + LWS_PRE, 2, LWS_WRITE_TEXT);
		if (m < 2) {
			lwsl_err("ERROR %d writing to ws\n", m);
			return -1;
		}
		break;

	default:
		break;
	}

	return 0;
}

#define LWS_PLUGIN_PROTOCOL_MINIMAL \
	{ \
		"lws-minimal", \
		callback_minimal, \
		0, \
		128, \
		0, NULL, 0 \
	}

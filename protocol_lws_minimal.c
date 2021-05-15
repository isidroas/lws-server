#if !defined (LWS_PLUGIN_STATIC)
#define LWS_DLL
#define LWS_INTERNAL
#include <libwebsockets.h>
#endif

#include <string.h>
#include "led-tcp.h"

static int
callback_minimal(struct lws *wsi, enum lws_callback_reasons reason,
			void *user, void *in, size_t len)
{
	int m;

	switch (reason) {

	case LWS_CALLBACK_RECEIVE:

        // Log received msg
        lwsl_user("msg received: %.*s\n",(int)len,(char *) in);
        led_tcp_send(len, in);
        
        // Send to led-driver poccess through tcp

        // Response string
        char *cadena="OK";

        // Extended response string
        char *cadena_ext[50];

        // Add terminator to string
		memcpy((char *)cadena_ext + LWS_PRE, cadena, 3);

        // Send response
		m = lws_write(wsi, ((unsigned char *)cadena_ext) + LWS_PRE, 2, LWS_WRITE_TEXT);

        // Check if success
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

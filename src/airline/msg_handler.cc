#define	_MSG_HANDLER_CC_

#include "common.h"
#include "msg_handler.h"

void commline_thread(msgrecv_cb_t cb)
{
	uint8_t buf[sizeof(msg_buf_t) + COMMLINE_MAX_BUF];
	msg_buf_t *mbuf=(msg_buf_t*)buf;
	int slptime=1;

	INFO << "Commline Thread created\n";
	while(1)
	{
		usleep(slptime);

		if(CL_SUCCESS!=cl_recvfrom_q(MTYPE(AIRLINE,0), mbuf, sizeof(buf))) {
			break;
		}
		slptime=mbuf->len?1:1000;
		if(mbuf->len) {
			cb(mbuf);
		}
	}
	INFO << "stopping commline_thread\n";
}

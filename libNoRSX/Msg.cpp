#include <NoRSX/Msg.h>

static vs32 dialog_action = 0;


static void dialog_handler(msgButton button, void *usrdata){
	dialog_action = button;
}

void sysutil_callback(u64 status, u64 param, void *usrdata){
}


MsgDialog::MsgDialog(Minimum *g){
	G=g;
	sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT1, sysutil_callback, NULL);

}

MsgDialog::~MsgDialog(){
	sysUtilUnregisterCallback(SYSUTIL_EVENT_SLOT1);
}

void MsgDialog::Dialog(msgType md, const char *message){
	msgDialogOpen2(md, message, dialog_handler, NULL, NULL);
	
	dialog_action = 0;
	while(dialog_action == 0){
		sysUtilCheckCallback();
		flip(G->context, 1);
	}
	
	msgDialogAbort();
}

int MsgDialog::GetResponse(vs32 button){
	if(dialog_action == button){
		return 1;
	}
	return -1;
}



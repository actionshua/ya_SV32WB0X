#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#define HCI_RX_EVT    (1 << 0)
#define HCI_TX_EVT    (1 << 1)
#define IPC_1_EVT     (1 << 2)
#define IPC_2_EVT     (1 << 3)
#define EVT_EXIT      (1 << 4)

#define HCI_HANDER 0

void suspend_hci_event_handler_task();
void resume_hci_event_handler_task();
void hci_event_handler();
void hci_event_set(u16 bit);

#endif

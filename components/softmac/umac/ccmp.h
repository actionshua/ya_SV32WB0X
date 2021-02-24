#ifndef _CCMP_H_
#define _CCMP_H_

void *lib80211_ccmp_init(int key_idx, u8 *key, size_t len);
void lib80211_ccmp_deinit(void *priv);
int lib80211_ccmp_encrypt(u8 *pkt, int *pktlen, int hdr_len, void *priv, u8 *pn);
int lib80211_ccmp_decrypt(u8 *pkt, int *pktlen, int hdr_len, void *priv);
void lib80211_ccmp_settxpn(u8 *pn, void *priv);

#endif /* _CCMP_H_ */

#ifndef __RC_MINSTREL_HT_H
#define __RC_MINSTREL_HT_H

/*
 * The number of streams can be changed to 2 to reduce code
 * size and memory footprint.
 */
#define MINSTREL_MAX_STREAMS	1
#define MINSTREL_STREAM_GROUPS	(4+1)

/* scaled fraction values */
#define MINSTREL_SCALE	16
#define MINSTREL_FRAC(val, div) (((val) << MINSTREL_SCALE) / div)
#define MINSTREL_TRUNC(val) ((val) >> MINSTREL_SCALE)


struct mcs_group {
	u32 flags;
	unsigned int streams;
	unsigned int duration[MCS_GROUP_RATES];
};

extern const struct mcs_group minstrel_mcs_groups[];

struct minstrel_rate_stats {
	/* current / last sampling period attempts/success counters */
	unsigned int attempts, last_attempts;
	unsigned int success, last_success;

	/* total attempts/success counters */
	u64 att_hist, succ_hist;

	/* current throughput */
	unsigned int cur_tp;

	/* packet delivery probabilities */
	unsigned int cur_prob, probability;

	/* maximum retry counts */
	unsigned int retry_count;
	unsigned int retry_count_rtscts;

	bool retry_updated;
	u8 sample_skipped;
};

struct minstrel_mcs_group_data {
	u8 index;
	u8 column;

	/* bitfield of supported MCS rates of this group */
	u8 supported;

	/* selected primary rates */
	unsigned int max_tp_rate;
	unsigned int max_tp_rate2;
	unsigned int max_prob_rate;

	/* MCS rate statistics */
	struct minstrel_rate_stats rates[MCS_GROUP_RATES];
};

struct minstrel_ht_sta {
	/* ampdu length (average, per sampling interval) */
	unsigned int ampdu_len;
	unsigned int ampdu_packets;

	/* ampdu length (EWMA) */
	unsigned int avg_ampdu_len;

	/* best throughput rate */
	unsigned int max_tp_rate;

	/* second best throughput rate */
	unsigned int max_tp_rate2;

	/* best probability rate */
	unsigned int max_prob_rate;

	/* time of last status update */
	unsigned long stats_update;

	/* overhead time in usec for each frame */
	unsigned int overhead;
	unsigned int overhead_rtscts;

	unsigned int total_packets;
	unsigned int sample_packets;

	/* tx flags to add for frames for this sta */
	u32 tx_flags;

	u8 sample_wait;
	u8 sample_tries;
	u8 sample_count;
	u8 sample_slow;

	/* current MCS group to be sampled */
	u8 sample_group;

	/* MCS rate group info and statistics */
	struct minstrel_mcs_group_data groups[MINSTREL_MAX_STREAMS * MINSTREL_STREAM_GROUPS];
};

struct minstrel_ht_sta_priv {
	union {
		struct minstrel_ht_sta ht;
		struct minstrel_sta_info legacy;
	};
	void *ratelist;
	void *sample_table;
    u8  n_ht_rate;
	bool is_ht;
};

extern const struct rate_control_ops mac80211_minstrel_ht;
void minstrel_ht_stats_open(void* sta_priv, rom_rc_minstrel_thunk_st *thunk);
#endif

/*
 * Copyright (C) 2008 Felix Fietkau <nbd@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __RC_MINSTREL_H
#define __RC_MINSTREL_H

#define DIV_ROUND_UP(n, d)	(((n) + (d) - 1) / (d))

struct minstrel_rate {
	int bitrate;
	int rix;

	unsigned int perfect_tx_time;
	unsigned int ack_time;

	int sample_limit;
	unsigned int retry_count;
	unsigned int retry_count_cts;
	unsigned int retry_count_rtscts;
	unsigned int adjusted_retry_count;

	u32 success;
	u32 attempts;
	u32 last_attempts;
	u32 last_success;

	/* parts per thousand */
	u32 cur_prob;
	u32 probability;

	/* per-rate throughput */
	u32 cur_tp;

	u64 succ_hist;
	u64 att_hist;
};

struct minstrel_sta_info {
	unsigned long stats_update;
	unsigned int sp_ack_dur;
	unsigned int rate_avg;

	unsigned int lowest_rix;

	unsigned int max_tp_rate;
	unsigned int max_tp_rate2;
	unsigned int max_prob_rate;
	unsigned int packet_count;
	unsigned int sample_count;
	int sample_deferred;

	unsigned int sample_idx;
	unsigned int sample_column;

	int n_rates;
	struct minstrel_rate *r;
	bool prev_sample;

	/* sampling table */
	u8 *sample_table;

};

struct minstrel_priv {
	void *hw;    
	u8 max_rates;
	u8 max_rate_tries;
	bool has_mrr;
	unsigned int cw_min;
	unsigned int cw_max;
	unsigned int max_retry;
	unsigned int ewma_level;
	unsigned int segment_size;
	unsigned int update_interval;
	unsigned int lookaround_rate;
	unsigned int lookaround_rate_mrr;
};

extern const struct rate_control_ops mac80211_minstrel;

#endif

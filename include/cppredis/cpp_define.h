#ifndef cpp_define_h__
#define cpp_define_h__

#include <vector>

namespace cpp_redis {
	const std::string g_crlf                     = "\r\n";
	const std::string g_nil                      = "nil";

	constexpr std::uint16_t g_send_times         = 500; //毫秒单位
	/******************常规操作***********************************/
	const std::string g_select_cmd               = "SELECT";
	const std::string g_auth_cmd                 = "AUTH";
	const std::string g_del_cmd                  = "DEL";
	const std::string g_exists_cmd               = "EXISTS";
	const std::string g_expire_cmd               = "EXPIRE";
	const std::string g_expire_at_cmd            = "EXPIREAT";
	const std::string g_ttl_cmd                  = "TTL";
	/****************字符串操作***********************************/
	const std::string g_setx_cmd                 = "SETEX";
	const std::string g_psetx_cmd                = "PSETEX";
	const std::string g_set_cmd                  = "SET";
	const std::string g_strsub_cmd               = "GETRANGE";//2.0之前叫substr
	const std::string g_incrby_cmd               = "INCRBY";
	const std::string g_get_cmd                  = "GET";
	const std::string g_get_set_cmd              = "GETSET";
	const std::string g_substr_cmd               = "SUBSTR";
	const std::string g_mget_cmd                 = "MGET";
	const std::string g_mset_cmd                 = "MSET";
	const std::string g_msetnx_cmd               = "MSETNX";
	const std::string g_append_cmd               = "APPEND";
	/******************list操作*************************************/
	const std::string g_rpush_cmd                = "RPUSH";
	const std::string g_lpush_cmd                = "LPUSH";
	const std::string g_llen_cmd                 = "LLEN";
	const std::string g_lrange_cmd               = "LRANGE";
	const std::string g_rpop_cmd                 = "RPOP";
	const std::string g_lpop_cmd                 = "LPOP";
	const std::string g_brpop_cmd                = "BRPOP";
	const std::string g_blpop_cmd                = "BLPOP";
	const std::string g_trim_cmd                 = "LTRIM";
	const std::string g_lindex_cmd               = "LINDEX";
	const std::string g_lset_cmd                 = "LSET";
	const std::string g_lrem_cmd                 = "LREM";
	const std::string g_rpoplpush_cmd            = "RPOPLPUSH";
	const std::string g_lpushx_cmd               = "LPUSHX";
	const std::string g_rpushx_cmd               = "RPUSHX";
	const std::string g_list_insert_cmd          = "LINSERT";
	const std::string g_brpoplpush_cmd           = "BRPOPLPUSH";
	/*******************set操作*************************************/
	const std::string g_sadd_cmd                 = "SADD";
	const std::string g_srem_cmd                 = "SREM";
	const std::string g_sismember_cmd            = "SISMEMBER";
	const std::string g_spop_elem_cmd            = "SPOP";
	const std::string g_srandmember_cmd          = "SRANDMEMBER";
	const std::string g_smove_cmd                = "SMOVE";
	const std::string g_ssize_cmd                = "SCARD"; //奇葩名字
	const std::string g_smembers_cmd             = "SMEMBERS";
	const std::string g_sinter_cmd               = "SINTER";
	const std::string  g_sinter_store_cmd        = "SINTERSTORE";
	const std::string g_sunion_cmd               = "SUNION";//
	const std::string  g_sunion_store_cmd        = "SUNIONSTORE";
	const std::string g_sdiff_cmd                = "SDIFF";
	const std::string g_sdiff_store_cmd          = "SDIFFSTORE";
	/*********************zset操作**************************************/
	const std::string g_zset_aggsum              = "SUM";
	const std::string g_zset_aggmin              = "MIN";
	const std::string g_zset_aggmax              = "MAX";
	const std::string g_zset_add_cmd             = "ZADD";
	const std::string g_zset_score_cmd           = "ZSCORE";
	const std::string g_zset_incrby_cmd          = "ZINCRBY";
	const std::string g_zset_card_cmd            = "ZCARD";
	const std::string g_zset_count_cmd           = "ZCOUNT";
	const std::string g_zset_range_cmd           = "ZRANGE";
	const std::string g_zset_revrane_cmd         = "ZREVRANGE";
	const std::string g_zset_range_score_cmd     = "ZRANGEBYSCORE";
	const std::string g_zset_rerange_score_cmd   = "ZREVRANGEBYSCORE";
	const std::string g_zset_rank_cmd            = "ZRANK";
	const std::string g_zset_revrank_cmd         = "ZREVRANK";
	const std::string g_zset_rem_cmd             = "ZREM";
	const std::string g_zset_remrangeby_rank_cmd = "ZREMRANGEBYRANK";
	const std::string g_zset_remrangebyscore_cmd = "ZREMRANGEBYSCORE";
	const std::string g_zset_rangebylex_cmd      = "ZRANGEBYLEX";
	const std::string g_zset_lexcount_cmd        = "ZLEXCOUNT";
	const std::string g_zset_remrangebylex_cmd   = "ZREMRANGEBYLEX";
	const std::string g_zset_union_store_mcd     = "ZUNIONSTORE";
	const std::string g_zset_inter_store_cmd     = "ZINTERSTORE";
	/***********************hash操作************************************/
	const std::string g_hash_set_cmd             = "HSET";
	const std::string g_hash_setx_cmd            = "HSETNX";
	const std::string g_hash_exists_cmd          = "HEXISTS";
	const std::string g_hash_get_cmd             = "HGET";
	const std::string g_hash_del_cmd             = "HDEL";
	const std::string g_hash_len_cmd             = "HLEN";
	const std::string g_hash_strlen_cmd          = "HSTRLEN";
	const std::string g_hash_incrby_cmd          = "HINCRBY";
	const std::string g_hash_mset_cmd            = "HMSET";
	const std::string g_hash_mget_cmd            = "HMGET";
	const std::string g_hash_keys_cmd            = "HKEYS";
	const std::string g_hash_vals_cmd            = "HVALS";
	const std::string g_hash_get_all_cmd         = "HGETALL";
	const std::string g_hash_incrby_float_cmd    = "HINCRBYFLOAT";
	/*******************************************************************/

	typedef std::string BYTES;
	typedef std::string KEY;
	typedef std::vector<KEY> KEYS;
	typedef std::vector<std::pair<KEY, BYTES> > PAIRS;//多个key一起发
	typedef PAIRS::value_type PAIR;
	typedef std::pair<int, BYTES> INT_VALUE;
	typedef std::vector<BYTES>VALUES;

	enum status
	{
		unconnected_                             = -1,
		results_                                 = 0,
		int_result_                              = 2,
		errors_                                  = 4,
		status_                                  = 8
	};

	enum redis_cmd
	{
		auth                                     = 0,
		select                                   = 1,
		set                                      = 2,
		setex                                    = 3,
		psetex                                   = 4,
		strsub                                   = 5,
		incrby                                   = 6,
		del                                      = 7,
		exists                                   = 8,
		get                                      = 9,
		expire                                   = 10,
		expire_at                                = 11,
		ttl                                      = 12,
		get_set                                  = 13,
		substr                                   = 14,
		mget                                     = 15,
		mset                                     = 16,
		msetnx                                   = 17,
		append                                   = 18,
		rpush                                    = 19,
		lpush                                    = 20,
		llen                                     = 21,
		lrange                                   = 22,
		rpop                                     = 23,
		lpop                                     = 24,
		brpop                                    = 25,
		blpop                                    = 26,
		ltrim                                    = 27,
		lindex                                   = 28,
		lset                                     = 29,
		lrem                                     = 30,
		rpoplpush                                = 31,
		lpushx                                   = 32,
		rpushx                                   = 33,
		list_insert                              = 34,
		brpoplpush                               = 35,
		sadd                                     = 36,
		srem                                     = 37,
		sismember                                = 38,
		spop_elem                                = 39,
		srandmember                              = 40,
		smove                                    = 41,
		ssize                                    = 42,
		smembers                                 = 43,
		sinter                                   = 44,
		ssinter_store                            = 45,
		sunion                                   = 46,
		ssunion_store                            = 47,
		sdiff                                    = 48,
		sdiff_store                              = 49,
		zset_add                                 = 50,
		zset_score                               = 51,
		zset_incrby                              = 52,
		zset_card                                = 53,
		zset_count                               = 54,
		zset_range                               = 55,
		zset_rank                                = 56,
		zset_rem                                 = 57,
		zset_revrank                             = 58,
		zset_revrange                            = 59,
		zset_lexcount                            = 60,
		zset_rangebylex                          = 61,
		zset_union_store                         = 62,
		zset_inter_store                         = 63,
		zset_range_score                         = 64,
		zset_remrangebylex                       = 65,
		zset_rerange_score                       = 66,
		zset_remrangebyscore                     = 67,
		zset_remrangeby_rank                     = 68,
		hash_set                                 = 69,
		hash_setx                                = 70,
		hash_exists                              = 71,
		hash_get                                 = 72,
		hash_del                                 = 73,
		hash_len                                 = 74,
		hash_mset                                = 75,
		hash_mget                                = 76,
		hash_vals                                = 77,
		hash_keys                                = 78,
		hash_strlen                              = 79,
		hash_incrby                              = 80,
		hash_get_all                             = 81,
		hash_incrby_float                        = 82,
	};

	enum request_type
	{
		none                                     = -1,
		string_request                           = 0,
		list_request                             = 1,
		set_request                              = 2,
		zset_request                             = 3,
		hash_request                             = 4,
	};

	enum aggregate_mothod
	{
		agg_none                                 = -1,
		agg_sum                                  = 0,
		agg_min                                  = 1,
		agg_max                                  = 2,
	};

	struct String {};
	struct List {};
	struct Set {};
	struct ZSet {};
	struct Hash {};
}

#endif // cpp_define_h__

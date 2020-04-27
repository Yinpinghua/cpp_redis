#ifndef cpp_zset_client_h__
#define cpp_zset_client_h__

#include "client_interface.hpp"

namespace cpp_redis {
	class zset_client :public client {
	public:
		zset_client() = default;
		virtual ~zset_client() {

		}

		//score ֻ��Ϊdouble,int float
		int zset_add(std::vector<std::string>&&keys) {
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::zset_add),std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code()!= status::int_result_){
				return 0;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : 0);
		}

		virtual std::string zset_score(std::string&& key,std::string&& member)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_score), std::forward<std::string>(key),std::forward<std::string>(member));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code()!=status::results_){
				return "";
			}

			const auto results = res->get_results();
			if (results.empty()){
				return "";
			}

			return ((results[0] == g_nil) ? "" :results[0]);
		}

		virtual std::string zset_incrby(std::string&& key,std::string&& increment,std::string&& member)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_incrby),std::forward<std::string>(key),
				std::forward<std::string>(increment),std::forward<std::string>(member));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return "";
			}

			const auto results = res->get_results();
			if (results.empty()) {
				return "";
			}

			return ((results[0] == g_nil) ? "" : results[0]);
		}

		virtual int zset_card(std::string&& key)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_card), std::forward<std::string>(key));
			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}
	
		virtual int zset_count(std::string&& key, std::string&& min, std::string&& max)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_count),
				std::forward<std::string>(key),std::forward<std::string>(min), std::forward<std::string>(max));

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}

		//����ͨ��ʹ�� WITHSCORES ѡ����ó�Ա������ score ֵһ�����أ�
		//�����б��� value1, score1, ..., valueN, scoreN �ĸ�ʽ��ʾ��
		//�ͻ��˿���ܻ᷵��һЩ�����ӵ��������ͣ��������顢Ԫ��ȡ�
		//��������
		virtual std::vector <std::string> zset_range(std::string&& key, std::string&& begin, std::string&& end,bool with_scores)
		{
			check_args();

			std::string msg;
			if (with_scores){
				msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_range), std::forward<std::string>(key),
					std::forward<std::string>(begin), std::forward<std::string>(end),"WITHSCORES"); //WITHSCORES ѡ��
			}else{
				msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_range), std::forward<std::string>(key),
					std::forward<std::string>(begin), std::forward<std::string>(end)); //WITHSCORES ѡ��
			}

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();

			if (res->get_result_code()!= status::results_){
				return {} ;
			}
			
			return std::move(res->get_results());
		}

		//����ͨ��ʹ�� WITHSCORES ѡ����ó�Ա������ score ֵһ�����أ�
		//�����б��� value1, score1, ..., valueN, scoreN �ĸ�ʽ��ʾ��
		//�ͻ��˿���ܻ᷵��һЩ�����ӵ��������ͣ��������顢Ԫ��ȡ�
		//�ݼ�����
		virtual std::vector <std::string> zset_revrange(std::string&& key, std::string&& begin, std::string&& end, bool with_scores)
		{
			check_args();

			std::string msg;
			if (with_scores) {
				msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_revrange), std::forward<std::string>(key),
					std::forward<std::string>(begin), std::forward<std::string>(end), "WITHSCORES"); //WITHSCORES ѡ��
			}
			else {
				msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_revrange), std::forward<std::string>(key),
					std::forward<std::string>(begin), std::forward<std::string>(end)); //WITHSCORES ѡ��
			}

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_) {
				return {} ;
			}

			return std::move(res->get_results());
		}

		//�������ڵ�score
		virtual std::vector <std::string> zset_range_score(std::string&& key, std::string&& min, std::string&& max,
			bool with_scores, bool limit, std::string&& limit_min, std::string &&limit_max)
		{
			check_args();

			std::string msg;
			if (with_scores) {
				if (limit){
					msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_range_score), std::forward<std::string>(key),
						std::forward<std::string>(min), std::forward<std::string>(max), "WITHSCORES", "LIMIT",//WITHSCORES ѡ��
						std::forward<std::string>(limit_min), std::forward<std::string>(limit_max));//limit��ʾ��Χ
				}else{
					msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_range_score), std::forward<std::string>(key),
						std::forward<std::string>(min), std::forward<std::string>(max), "WITHSCORES"); //WITHSCORES ѡ��
				}
			}else {
				if (limit) {
					msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_range_score), std::forward<std::string>(key),
						std::forward<std::string>(min), std::forward<std::string>(max), "LIMIT",
						std::forward<std::string>(limit_min), std::forward<std::string>(limit_max));//limit��ʾ��Χ
				}else {
					msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_range_score), std::forward<std::string>(key),
						std::forward<std::string>(min), std::forward<std::string>(max));
				}
			}

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_) {
				return {} ;
			}

			return std::move(res->get_results());
		}

		virtual std::vector <std::string> zset_revrange_score(std::string&& key, std::string&& max, std::string&& min,
			bool with_scores, bool limit, std::string&& limit_min, std::string&& limit_max)
		{
			check_args();

			std::string msg;
			if (with_scores) {
				if (limit) {
					msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_rerange_score), std::forward<std::string>(key),
						std::forward<std::string>(max), std::forward<std::string>(min), "WITHSCORES", "LIMIT",//WITHSCORES ѡ��
						std::forward<std::string>(limit_min), std::forward<std::string>(limit_max));//limit��ʾ��Χ
				}else {
					msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_rerange_score), std::forward<std::string>(key),
						std::forward<std::string>(max), std::forward<std::string>(min), "WITHSCORES"); //WITHSCORES ѡ��
				}
			}
			else {
				if (limit) {
					msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_rerange_score), std::forward<std::string>(key),
						std::forward<std::string>(max), std::forward<std::string>(min), "LIMIT",
						std::forward<std::string>(limit_min), std::forward<std::string>(limit_max));//limit��ʾ��Χ
				}else {
					msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_rerange_score), std::forward<std::string>(key),
						std::forward<std::string>(max), std::forward<std::string>(min));
				}
			}

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_) {
				return {};
			}

			return std::move(res->get_results());
		}

		//���򣬴�0��ʼ
		virtual int zset_rank(std::string&& key, std::string&& member)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_rank),std::forward<std::string>(key),std::forward<std::string>(member));

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return -1;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : -1);
		}

		//���򣬴�0��ʼ�����Ӵ�Ŀ�ʼ��
		virtual int zset_revrank(std::string&& key, std::string&& member)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_revrank),std::forward<std::string>(key),std::forward<std::string>(member));

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return -1;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : -1);
		}


		virtual bool zset_rem(std::vector<std::string>&&keys)
		{
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::zset_rem),std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));
			
			const auto res = socket_->get_responese();
			if (res->get_result_code() !=status::int_result_){
				return false;
			}

			const auto results = res->get_int_results();
			if (results.empty()){
				return false;
			}

			return results[0]>0 ?true:false;
		}

		//�Ƴ����� key �У�ָ������(rank)�����ڵ����г�Ա
		virtual int zset_remrangeby_rank(std::string&& key, std::string&& begin, std::string&& end)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_remrangeby_rank),std::forward<std::string>(key),std::forward<std::string>(begin),
				std::forward<std::string>(end));
			
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return false;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : 0);
		}

		virtual int zset_remrangebyscore(std::string&& key, std::string&& min, std::string&& max)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_remrangebyscore), std::forward<std::string>(key), std::forward<std::string>(min),
				std::forward<std::string>(max));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return false;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : 0);
		}

		virtual int zset_union_store(std::vector<std::string>&& keys, aggregate_mothod mothod)
		{
			if (mothod >aggregate_mothod::agg_none && 
				mothod <=aggregate_mothod::agg_max) {
				keys.emplace_back("AGGREGATE");
				keys.emplace_back(request_->get_aggregate_mothod(mothod));
			}

			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::zset_union_store), 
				std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_){
				return 0;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : 0);
		}

		virtual int zset_inter_store(std::vector<std::string>&& keys, aggregate_mothod mothod)
		{
			if (mothod > aggregate_mothod::agg_none&&
				mothod <= aggregate_mothod::agg_max) {
				keys.emplace_back("AGGREGATE");
				keys.emplace_back(request_->get_aggregate_mothod(mothod));
			}

			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::zset_inter_store),
				std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}

		/**************************************************************���¼����ӿڲ�����************************************************************************/
		//�Ϸ��� min �� max �����������(����[�� ����(��ʾ�����䣨ָ����ֵ���ᱻ�����ڷ�Χ֮�ڣ��� ��[���ʾ�����䣨ָ����ֵ�ᱻ�����ڷ�Χ֮�ڣ���
		//����ֵ + �� - �� min �����Լ� max �����о�����������壬 ���� + ��ʾ�����ޣ� �� - ��ʾ�����ޡ� 
		//��ˣ� ��һ�����г�Ա�ķ�ֵ����ͬ�����򼯺Ϸ������� ZRANGEBYLEX <zset> -+�� ����������򼯺��е�����Ԫ�ء�
		virtual std::vector <std::string> zset_rangebylex(std::string&& key, std::string&& min,
			std::string&& max, bool limit, std::string&& limit_min, std::string&& limit_max)
		{
			check_args();
			std::string msg;
			if (limit){
				msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_rangebylex), std::forward<std::string>(key),
					std::forward<std::string>(min),std::forward<std::string>(max),std::forward<std::string>(limit_min),std::forward<std::string>(limit_max));
			}else{
				msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_rangebylex), std::forward<std::string>(key),
					std::forward<std::string>(min), std::forward<std::string>(max));
			}

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_) {
				return {};
			}

			return std::move(res->get_results());
		}

		virtual int zset_lexcount(std::string&& key, std::string&& min, std::string&& max)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_lexcount),std::forward<std::string>(key),
				std::forward<std::string>(min), std::forward<std::string>(max));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ?results[0]: 0);
		}

		virtual int zset_remrangebylex(std::string&& key, std::string&& min, std::string&& max)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::zset_remrangebylex), std::forward<std::string>(key),
				std::forward<std::string>(min), std::forward<std::string>(max));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : 0);
		}

	};
}//cpp_redis

#endif // cpp_zset_client_h__

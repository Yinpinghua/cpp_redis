#ifndef cpp_set_client_h__
#define cpp_set_client_h__

#include "client_interface.hpp"

namespace cpp_redis {
	class set_client :public client {
	public:
		set_client() = default;
		virtual ~set_client()
		{

		}

		//���ص�ǰset�ĸ���
		int set_add(std::vector<std::string>&& keys)
		{
			check_args();

			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::sadd),std::forward<std::vector<std::string>>(keys));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0]:0);
		}

		//���ص�ǰset�ĸ���,ɾ��ʧ��ֱ�ӷ���-1
		int set_delete_elem(std::vector<std::string>&& keys)
		{
			check_args();

			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::srem),std::forward<std::vector<std::string>>(keys));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}

		//�Ƿ���ture,����һ��Ϊfalse
		virtual bool set_is_member(std::string&& key, std::string&& value)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::sismember),
				std::forward<std::string>(key), std::forward<std::string>(value));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return false;
			}

			const auto result = res->get_int_results();
			if (result.empty()) {
				return false;
			}

			return ((result[0] == 1) ? true : false);
		}

		//����Ƴ�һ��Ԫ��
		virtual std::string set_rdel_elem(std::string&& key)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::spop_elem), std::forward<std::string>(key));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return false;
			}

			const auto result = res->get_results();
			if (result.empty()) {
				return "";
			}

			return ((result[0] == g_nil) ? "" : result[0]);
		}

		//count >0��ʾԪ�ز����ظ�, <0��ʾԪ�ػ��ظ�
		virtual RESULTS_TYPE set_rand_elem(std::string&& key, int count)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::srandmember), std::forward<std::string>(key), std::move(unit::int_to_string(count)));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return{};
			}

			auto result = res->get_results();
			if (result.empty() || result[0] == g_nil) {
				return {};
			}

			return  std::move(result);
		}

		virtual bool set_move_elem(std::string&& src_key, std::string&& dst_key, std::string&& member)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::smove), std::forward<std::string>(src_key),
				std::forward<std::string>(dst_key), std::forward<std::string>(member));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return false;
			}

			const auto resulut = res->get_int_results();
			if (resulut.empty()) {
				return false;
			}

			return ((resulut[0] == 1) ? true : false);
		}

		virtual size_t set_get_size(std::string&& key)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::ssize), std::forward<std::string>(key));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto resulut = res->get_int_results();
			if (resulut.empty()) {
				return 0;
			}

			return resulut[0];
		}

		virtual RESULTS_TYPE set_get_all_member(std::string&& key)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::smembers), std::forward<std::string>(key));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return{};
			}

			auto result = res->get_results();
			if (result.empty() || result[0] == g_nil) {
				return {};
			}

			return  std::move(result);
		}

		//�󼯺ϵĽ��������һ��Ϊ�գ��ͷ��ؿ�
		virtual RESULTS_TYPE set_sinter(std::vector<std::string>&& keys)
		{
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::sinter),std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return{};
			}

			auto result = res->get_results();
			return ((!result.empty()) ? std::move(result) : std::move(std::vector<std::string>{}));
		}

		//�󼯺ϵĽ��������һ��Ϊ�գ��ͷ��ؿ�,����������һ���ط�
		virtual int set_inter_store(std::vector<std::string>&& keys)
		{
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::ssinter_store),std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			auto result = res->get_int_results();

			return  ((!result.empty()) ? result[0] :0);
		}

		//�󼯺ϵĲ�����,������key����Ϊ�� 
		//(����һ�����ϵ�ȫ����Ա���ü��������и������ϵĲ���)
		//A{1:1234,2:5678,37895,4:910245} B{1:1234,2:7895,3:78945}
		//A U B={1234,5678,7895,10245}
		virtual RESULTS_TYPE set_union(std::vector<std::string>&&keys)
		{
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::sunion), std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return{};
			}

			auto result = res->get_results();
			if (result.empty()) {
				return {};
			}

			return  std::move(result);
		}

		//�󼯺ϵĲ��������һ��Ϊ�գ��ͷ��ؿ�,����������һ���ط�
		//(����һ�����ϵ�ȫ����Ա���ü��������и������ϵĲ���)
		//src_key�����Ǳ����Լ�
		virtual int set_union_store(std::vector<std::string>&&keys)
		{
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::ssunion_store),std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : 0);
		}

		//����һ�����ϵ�ȫ����Ա���ü��������и�������֮��Ĳ��
	   //�����ڵ� key ����Ϊ�ռ���

		virtual RESULTS_TYPE set_diff(std::vector<std::string>&& keys)
		{
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::sdiff), std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return{};
			}

			auto results = res->get_results();

			return  ((!results.empty()) ? std::move(results) : std::move(RESULTS_TYPE()));
		}

		//����һ�����ϵ�ȫ����Ա���ü��������и�������֮��Ĳ��
		//�����ڵ� key ����Ϊ�ռ���Ȼ�󱣴�����
		virtual int set_diff_store(std::vector<std::string>&&keys)
		{
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::sdiff_store),std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			auto results = res->get_int_results();


			return  ((!results.empty()) ? results[0]:0);
		}

	};
}

#endif // cpp_set_client_h__

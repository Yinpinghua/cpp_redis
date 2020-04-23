#ifndef cpp_redis_list_h__
#define cpp_redis_list_h__

#include "client_interface.hpp"

namespace cpp_redis {
	class list_client:public client {
	public:
		list_client() = default;

		virtual~list_client() {

		}

		//list����ʱҪѡ����, ����tuple:��������
		//������������ֵ����
		//β���뷨
		virtual std::tuple<bool, int> list_rpush(std::string&& key, std::string&& value)
		{
			check_args();

			std::string msg = request_->req_n_key_value(request_->get_cmd(cpp_redis::rpush), std::forward<std::string>(key), std::forward<std::string>(value));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			const auto int_result = res->get_int_results();
			if (res->get_result_code() != status::errors_ && !int_result.empty()) {
				return std::make_tuple(true, int_result[0]);
			}

			return std::make_tuple(false, 0);
		}

		//����ʱ�ж�key�Ƿ���ڣ����ڲ��벻����ʲôҲ����
		virtual std::tuple<bool, int> list_rpush_if(std::string&& key, std::string&& value)
		{
			check_args();

			std::string msg = request_->req_n_key_value(request_->get_cmd(cpp_redis::rpushx), std::forward<std::string>(key), std::forward<std::string>(value));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			const auto int_result = res->get_int_results();
			if (res->get_result_code() != status::errors_ && !int_result.empty()) {
				return std::make_tuple(true, int_result[0]);
			}

			return std::make_tuple(false, 0);
		}

		//ͷ���뷨
		virtual std::tuple<bool, int> list_lpush(std::string&& key, std::string&& value)
		{
			check_args();

			std::string msg = request_->req_n_key_value(request_->get_cmd(cpp_redis::lpush), std::forward<std::string>(key), std::forward<std::string>(value));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			const auto int_result = res->get_int_results();
			if (res->get_result_code() != status::errors_ && !int_result.empty()) {
				return std::make_tuple(true, int_result[0]);
			}

			return std::make_tuple(false, 0);
		}

		//����ʱ�ж�key�Ƿ���ڣ����ڲ��벻����ʲôҲ����
		virtual std::tuple<bool, int> list_lpush_if(std::string&& key, std::string&& value)
		{
			check_args();

			std::string msg = request_->req_n_key_value(request_->get_cmd(cpp_redis::lpushx), std::forward<std::string>(key), std::forward<std::string>(value));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			const auto int_result = res->get_int_results();
			if (res->get_result_code() != status::errors_ && !int_result.empty()) {
				return std::make_tuple(true, int_result[0]);
			}

			return std::make_tuple(false, 0);
		}

		virtual int32_t list_size(std::string&& key)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::llen), std::forward<std::string>(key));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			const auto int_result = res->get_int_results();
			if (res->get_result_code() == status::errors_ || int_result.empty()) {
				return -1;
			}

			return int_result[0];
		}

		/************������һ��,�±���㿪ʼ**************************************/
		virtual  RESULTS_TYPE list_range(std::string&& key, int start, int end)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::lrange), std::forward<std::string>(key),
				std::move(unit::int_to_string(start)), std::move(unit::int_to_string(end)));

			socket_->send_msg(std::move(msg));
			RESULTS_TYPE results;
			const auto res = socket_->get_responese();

			if (res->get_result_code() == status::errors_) {
				return std::move(results);
			}

			//������������ֵ
			results = res->get_results();
			return std::move(results);
		}

		//��һ����ʼ��,����ԭʼ�Ĳ��뷽��
		virtual std::string list_lpop(std::string&& key)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::lpop), std::forward<std::string>(key));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();

			if (res->get_result_code() == status::errors_) {
				return "";
			}

			const auto results = res->get_results();

			if (results.empty()) {
				return "";
			}

			return results[0];
		}

		//������浯��Ԫ�أ�Ԫ�ص����ˣ�redisֱ��ɾ��
		virtual std::string list_rpop(std::string&& key)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::rpop), std::forward<std::string>(key));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();

			if (res->get_result_code() == status::errors_) {
				return "";
			}

			const auto results = res->get_results();

			if (results.empty()) {
				return "";
			}

			//������ֵ 
			return results[0];
		}

		//�������Ԫ��
		//���ص��Ǽ�ֵ��
		virtual std::string list_brpop(std::string&& key, size_t timeout = 0)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::brpop), std::forward<std::string>(key), std::move(unit::int_to_string(timeout)));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() == status::errors_ ||
				res->get_result_code() == status::unconnected_) {
				return "";
			}

			const auto results = res->get_results();
			if (results.empty() || results.size() < 2) {
				return {};
			}

			return results[1];
		}

		//������ǰԪ��
		//���ص��Ǽ�ֵ��
		virtual std::string list_blpop(std::string&& key, size_t timeout = 0)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::blpop), std::forward<std::string>(key), std::move(unit::int_to_string(timeout)));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() == status::errors_ ||
				res->get_result_code() == status::unconnected_) {
				return "";
			}

			const auto results = res->get_results();
			if (results.empty() || results.size() < 2) {
				return {};
			}

			return results[1];
		}

		//�б�ֻ����ָ�������ڵ�Ԫ�أ�����ָ������֮�ڵ�Ԫ�ض�����ɾ����
		virtual bool list_trim(std::string&& key, int start, int end)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::ltrim), std::forward<std::string>(key),
				std::move(unit::int_to_string(start)), std::move(unit::int_to_string(end)));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_) {
				return false;
			}

			return true;
		}
		//������ȡ�б��е�Ԫ��.�� -1 ��ʾ�б�����һ��Ԫ�أ�//-2 ��ʾ�б�ĵ����ڶ���Ԫ�أ��Դ����ơ�
		virtual std::string list_index(std::string&& key, int index)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::lindex), std::forward<std::string>(key), std::move(unit::int_to_string(index)));
			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_) {
				return "";
			}

			const auto  results = res->get_results();
			if (results.empty()) {
				return "";
			}

			if (results[0] == g_nil) {
				return "";
			}

			return results[0];
		}

		//ָ������������Ԫ��ֵ
		virtual bool list_set(std::string&& key, std::string&& value, int index)
		{
			check_args();

			auto pair = request_->make_pair(std::forward<std::string>(key), std::forward<std::string>(value));
			std::string msg = request_->req_key_value_has_index(request_->get_cmd(cpp_redis::lset), std::move(pair), std::forward<std::string>(unit::int_to_string(index)));
			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();

			if (res->get_result_code() == status::status_) {
				return true;
			}

			return false;
		}

		//û���Ƴ���Ϊ0 �����Ƴ��ʹ���0��index��ʾlist����ʼλ��,һ���0��ʼɾ��,-1��ʾ���һ��Ԫ��ɾ��
		//�����0��ʼɾ�����ж���ɾ������
		//�����-1��ʼɾ��,��ֻ��ɾ��һ��Ԫ��
		virtual std::tuple<bool, int> list_del_elem(std::string&& key, std::string&& value, int index = 0)
		{
			check_args();

			auto pair = request_->make_pair(std::forward<std::string>(key), std::forward<std::string>(value));
			std::string msg = request_->req_key_value_has_index(request_->get_cmd(cpp_redis::lrem), std::move(pair), std::forward<std::string>(unit::int_to_string(index)));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return std::make_tuple(false, -1);
			}

			const auto results = res->get_int_results();
			if (results.empty()) {
				return std::make_tuple(false, -1);
			}

			return std::make_tuple(true, results[0]);
		}

		//���һ��Ԫ���ƶ�������һ��listȥ
		virtual std::string list_rpoplpush(std::string&& src_key, std::string&& dst_key)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::rpoplpush), std::forward<std::string>(src_key), std::forward<std::string>(dst_key));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return "";
			}

			const auto results = res->get_results();
			if (results.empty()) {
				return "";
			}

			return results[0];
		}

		//���һ��Ԫ���ƶ�������һ��listȥ
		//timeout:0��Զ�ȴ�
		virtual std::string list_brpoplpush(std::string&& src_key, std::string&& dst_key, int timeout = 0)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::brpoplpush), std::forward<std::string>(src_key),
				std::forward<std::string>(dst_key), std::move(unit::int_to_string(timeout)));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_) {
				return "";
			}

			const auto results = res->get_results();
			if (results.empty()) {
				return "";
			}

			return results[0];
		}

		virtual int list_insert_before(std::string&& key, std::string&& dst_value, std::string&& insert_value)
		{
			check_args();

			const std::string distance = "before";
			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::list_insert), std::forward<std::string>(key), std::move(distance),
				std::forward<std::string>(dst_value), std::forward<std::string>(insert_value));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_)
			{
				return -1;
			}

			const auto int_result = res->get_int_results();
			if (int_result.empty()) {
				return -1;
			}

			return int_result[0];
		}

		virtual int list_insert_after(std::string&& key, std::string&& dst_value, std::string&& insert_value)
		{
			check_args();

			const std::string distance = "after";
			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::list_insert), std::forward<std::string>(key), std::move(distance),
				std::forward<std::string>(dst_value), std::forward<std::string>(insert_value));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_)
			{
				return -1;
			}

			const auto int_result = res->get_int_results();
			if (int_result.empty()) {
				return -1;
			}

			return int_result[0];
		}
	};
}

#endif // cpp_redis_list_h__

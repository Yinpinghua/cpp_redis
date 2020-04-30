#ifndef cpp_redis_string_h__
#define cpp_redis_string_h__

#include "client_interface.hpp"

namespace cpp_redis {
	class string_client:public client {
	public:
		string_client() = default;

		virtual~string_client()
		{

		}

		virtual bool setex(std::string&& key, std::string&& value,std::string && seconds)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::setex),
				std::forward<std::string>(key),std::forward<std::string>(seconds),std::forward<std::string>(value));

			if (!socket_->send_msg(std::move(msg))){
				return false;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_){
				return false;
			}

			return true;
		}

		virtual bool psetex(std::string&& key, std::string&& value, std::string&& milliseconds)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::psetex),std::forward<std::string>(key),
				std::forward<std::string>(milliseconds), std::forward<std::string>(value));

			if (!socket_->send_msg(std::move(msg))){
				return false;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_){
				return false;
			}

			return true;
		}

		virtual bool set(std::string&& key, std::string&& value)
		{
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::set),
				std::forward<std::string>(key), std::forward<std::string>(value));

			if (!socket_->send_msg(std::move(msg))){
				return false;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_){
				return false;
			}

			return true;
		}

		virtual int setnx(std::string&& key, std::string&& value)
		{
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::setnx),
				std::forward<std::string>(key), std::forward<std::string>(value));

			if (!socket_->send_msg(std::move(msg))) {
				return 0;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0]:0);
		}

		virtual bool setnx_has_seconds(std::string&& key, std::string&& value, std::string&& seconds)
		{
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::set),
				std::forward<std::string>(key), std::forward<std::string>(value), "EX", std::forward<std::string>(seconds), "NX");

			if (!socket_->send_msg(std::move(msg))) {
				return false;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_){
				return false;
			}

			return true;
		}

		virtual bool setxx(std::string&& key, std::string&& value, std::string&& seconds)
		{
			std::string msg=request_->req_n_key(request_->get_cmd(redis_cmd::set),
					std::forward<std::string>(key), std::forward<std::string>(value), "EX", std::forward<std::string>(seconds), "XX");

			if (!socket_->send_msg(std::move(msg))) {
				return false;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_) {
				return false;
			}

			return true;
		}

		virtual bool setnx_has_milliseconds(std::string&& key, std::string&& value,std::string&& milliseconds)
		{
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::set),
				std::forward<std::string>(key), std::forward<std::string>(value), "PX", std::forward<std::string>(milliseconds), "NX");

			if (!socket_->send_msg(std::move(msg))) {
				return false;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_){
				return false;
			}

			return true;
		}

		virtual bool setxx_has_milliseconds(std::string&& key, std::string&& value, std::string&& milliseconds)
		{
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::set),
		std::forward<std::string>(key), std::forward<std::string>(value), "PX", std::forward<std::string>(milliseconds),"XX");
			
			if (!socket_->send_msg(std::move(msg))) {
				return false;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_) {
				return false;
			}

			return true;
		}

		//sub_str;//2.0֮ǰ��SUBSTR 
		virtual std::string get_range(std::string&& key, std::string&& start, std::string&& end)
		{
			check_args();
			
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::strsub),std::forward<std::string>(key),
				std::forward<std::string>(start),std::forward<std::string>(end));

			if (!socket_->send_msg(std::move(msg))) {
				return "";
			}

			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_){
				return "";
			}

			const auto results = res->get_results();

			return ((results.empty() ||results[0] == g_nil) ? "": std::move(results[0]));
		}

		//��������,�ʹ���key,Ȼ��������1
		virtual int incr(std::string&& key)
		{
			check_args();
			
			std::string  msg = request_->req_n_key(request_->get_cmd(cpp_redis::incr),
				std::forward<std::string>(key));

			if (!socket_->send_msg(std::move(msg))) {
				return -1;
			}

			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::int_result_&&
				res->get_result_code() != status::status_){
				return -1;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : -1);
		}

		//��������,�ʹ���key,Ȼ��������
		virtual int incr_by_increment(std::string&& key,std::string&& increment)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::incrby), std::forward<std::string>(key), 
				std::forward<std::string>(increment));

			if (!socket_->send_msg(std::move(msg))) {
				return -1;
			}

			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::int_result_&&
				res->get_result_code() != status::status_) {
				return -1;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : -1);
		}

		virtual std::string incr_by_float(std::string&& key, std::string&& increment)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::incr_by_float), std::forward<std::string>(key),
				std::forward<std::string>(increment));

			if (!socket_->send_msg(std::move(msg))) {
				return "";
			}

			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_&&
				res->get_result_code() != status::status_){
				return "";
			}

			const auto results = res->get_results();

			return (!results.empty() && results[0] != g_nil ? std::move(results[0]) : "");
		}

		virtual int decr(std::string&& key)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::decr),
				std::forward<std::string>(key));
			
			if (!socket_->send_msg(std::move(msg))) {
				return -1;
			}

			const auto res = socket_->get_responese();
			
			if (res->get_result_code() != status::int_result_&&
				res->get_result_code() != status::status_){
				return -1;
			}

			const auto int_results = res->get_int_results();

			return ((!int_results.empty()) ? int_results[0] : -1);
		}

		virtual int decr_increment(std::string&& key,std::string&& increment)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::decyby),
				std::forward<std::string>(key),std::forward<std::string>(increment));

			if (!socket_->send_msg(std::move(msg))) {
				return -1;
			}

			const auto res = socket_->get_responese();

			const auto int_results = res->get_int_results();

			return ((!int_results.empty()) ? int_results[0]: -1);
		}

		virtual std::string get_reflect_value(std::string&& key)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::get), std::forward<std::string>(key));

			if (!socket_->send_msg(std::move(msg))) {
				return "";
			}

			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_) {
				return "";
			}

			const auto results = res->get_results();

			return ((!results.empty()) ? std::move(results[0]) : "");
		}

		virtual std::string get_set_key(std::string&& key, std::string&& value)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::get_set), 
				std::forward<std::string>(key), std::forward <std::string>(value));

			if (!socket_->send_msg(std::move(msg))) {
				return "";
			}

			const auto res = socket_->get_responese();

			const auto results = res->get_results();

			return ((!results.empty()) ? std::move(results[0]) : "");
		}

		virtual std::string substr_reflect_value(std::string&& key, int start, int end)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::substr), std::forward<std::string>(key),
				std::move(unit::int_to_string(start)), std::move(unit::int_to_string(end)));

			if (!socket_->send_msg(std::move(msg))) {
				return "";
			}

			const auto res = socket_->get_responese();

			const auto results = res->get_results();
			
			return ((!results.empty()) ? std::move(results[0]) : "");
		}

		virtual std::vector<std::string>  multi_get_keys(std::vector<std::string>&&keys)
		{
			check_args();

			std::string msg = request_->req_n_keys(request_->get_cmd(cpp_redis::mget), std::forward<std::vector<std::string>>(keys));

			if (!socket_->send_msg(std::move(msg))) {
				return {};
			}

			const auto res = socket_->get_responese();

			if (res->get_result_code() != status::results_&&
				res->get_result_code() != status::status_) {
				return {};
			}

			return std::move(res->get_results());
		}

		/****************�˽ӿ���Ҫ��key,value,key,value....*************************/
		virtual bool multi_set_keys(std::vector<std::string>&& keys)
		{
			check_args();
			std::string msg = request_->req_n_keys(request_->get_cmd(cpp_redis::mset), std::forward<std::vector<std::string>>(keys));

			if (!socket_->send_msg(std::move(msg))) {
				return false;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_) {
				return false;
			}

			return true;
		}

		/****************�˽ӿ���Ҫ��key,value,key,value....*************************/
		//������ key ���ɹ����ã����� 1 �� ������и��� key ������ʧ��(������һ�� key �Ѿ�����)����ô���� 0,��ʾʧ��
		virtual int multi_set_if_not_set(std::vector<std::string>&&keys)
		{
			check_args();

			std::string msg = request_->req_n_keys(request_->get_cmd(cpp_redis::msetnx), std::forward<std::vector<std::string>>(keys));

			if (!socket_->send_msg(std::move(msg))) {
				return 0;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_&&
				res->get_result_code() != status::status_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : -1);
		}

		//��ָ��key׷��ֵ
		virtual int append_value(std::string&& key, std::string&& appended_value)
		{
			check_args();

			std::string msg = request_->req_n_key(request_->get_cmd(cpp_redis::append),
				std::forward<std::string>(key), std::forward<std::string>(appended_value));

			if (!socket_->send_msg(std::move(msg))) {
				return -1;
			}

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_&&
				res->get_result_code() != status::status_) {
				return -1;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0]:-1);
		}
	};
}
#endif // cpp_redis_string_h__

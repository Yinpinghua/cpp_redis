#ifndef cpp_hash_client_h__
#define cpp_hash_client_h__

#include "client_interface.hpp"

namespace cpp_redis
{
	class hash_client :public client {
	public:
		hash_client()          = default;
		virtual ~hash_client() {

		}

		//�� HSET �����ڹ�ϣ�����´��� field �򲢳ɹ�Ϊ������ֵʱ�� ����� 1 
		//����� field �Ѿ������ڹ�ϣ�� ���� HSET ����ɹ�ʹ����ֵ���������ľ�ֵ�� ��ô����� 0
		virtual int hash_set(std::string&& key, std::string&& field, std::string&& value)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_set),std::forward<std::string>(key),
				std::forward<std::string>(field), std::forward<std::string>(value));
		
			socket_->send_msg(std::move(msg));
			const auto res  = socket_->get_responese();
			if (res->get_result_code() != status::int_result_ &&
				res->get_result_code() != status::status_){
				return 0;
			}

			const auto results = res->get_int_results();

			return ((!results.empty())?results[0]:0);
		}

		//��string���ݽṹһ��,����ʵ�ֲַ�ʽ��
		//HSETNX ���������óɹ�ʱ���� 1 �� �ڸ������Ѿ����ڶ�����ִ�����ò���ʱ���� 0.
		//����������Ѿ������ڹ�ϣ���У� ��ô�������ִ�����ò�����
		virtual int hash_setx(std::string&& key, std::string&& field, std::string&& value)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_setx), std::forward<std::string>(key),
				std::forward<std::string>(field), std::forward<std::string>(value));

			socket_->send_msg(std::move(msg));
			const auto res  = socket_->get_responese();
			if (res->get_result_code() != status::int_result_ &&
				res->get_result_code() != status::status_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}

		virtual int hash_exists(std::string&& key, std::string&& field)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_exists), std::forward<std::string>(key),
				std::forward<std::string>(field));

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_ &&
				res->get_result_code() != status::status_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}

		virtual std::string hash_get(std::string&& key, std::string&& field)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_get),std::forward<std::string>(key), std::forward<std::string>(field));

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();
			if (res->get_result_code()!= status::results_ &&
				res->get_result_code() != status::status_){
				return "";
			}

			const auto results = res->get_results();
			if (results.empty()){
				return "";
			}

			return ((results[0] == g_nil) ? "" : std::move(results[0]));
		}

		virtual int hash_del(std::vector<std::string>&& fields)
		{
			check_args();

			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::hash_del), std::forward<std::vector<std::string>>(fields));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_ &&
				res->get_result_code() != status::status_){
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}

		virtual int hash_len(std::string&& key)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_len),std::forward<std::string>(key));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_ &&
				res->get_result_code() != status::status_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}

		virtual int hash_strlen(std::string&& key, std::string&& field)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_strlen), std::forward<std::string>(key),
				std::forward<std::string>(field));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_ &&
				res->get_result_code() != status::status_) {
				return 0;
			}

			const auto results = res->get_int_results();
			return ((!results.empty()) ? results[0] : 0);
		}

		//��������ֵ
		//һ���µĹ�ϣ��������ִ��HINCRBY ����(ע��ط�)
		virtual int hash_incrby(std::string&& key, std::string&& field, std::string&& increment)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_incrby), std::forward<std::string>(key),
				std::forward<std::string>(field),std::forward<std::string>(increment));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_ &&
				res->get_result_code() != status::status_) {
				return 0;
			}

			const auto results = res->get_int_results();

			return ((!results.empty()) ? results[0] : 0);
		}

		virtual std::string hash_incrby_float(std::string&& key, std::string&& field, std::string&& increment)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_incrby_float), std::forward<std::string>(key),
				std::forward<std::string>(field), std::forward<std::string>(increment));

			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_ &&
				res->get_result_code() != status::status_) {
				return"";
			}

			const auto results = res->get_results();

			return ((!results.empty()) ? std::move(results[0]) : "");
		}


		virtual bool hash_mset(std::vector<std::string>&& keys)
		{
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::hash_mset), std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::status_){
				return false;
			}

			return true;
		}

		virtual std::vector <std::string> hash_mget(std::vector<std::string>&& keys)
		{
			std::string msg = request_->req_n_keys(request_->get_cmd(redis_cmd::hash_mget), std::forward<std::vector<std::string>>(keys));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_ &&
				res->get_result_code() != status::status_){
				return {} ;
			}

			return std::move(res->get_results());
		}

		//�������е�keys
		virtual std::vector <std::string> hash_keys(std::string&& key)
		{
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_keys), std::forward<std::string>(key));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_ &&
				res->get_result_code() != status::status_){
				return {} ;
			}

			return std::move(res->get_results());
		}


		//����key�е�����ֵ
		virtual std::vector <std::string> hash_vals(std::string&& key)
		{
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_vals),
				std::forward<std::string>(key));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_ &&
				res->get_result_code() != status::status_){
				return {} ;
			}

			return std::move(res->get_results());
		}
		
		//����key�е����ֵ
		virtual  std::vector <std::string> hash_get_all(std::string&& key)
		{
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_get_all), 
				std::forward<std::string>(key));
			socket_->send_msg(std::move(msg));

			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::results_ && 
				res->get_result_code() != status::status_){
				return  {} ;
			}

			return std::move(res->get_results());
		}

	};
}

#endif // cpp_hash_client_h__

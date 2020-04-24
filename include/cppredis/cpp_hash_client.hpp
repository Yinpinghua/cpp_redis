#ifndef cpp_hash_client_h__
#define cpp_hash_client_h__

#include "client_interface.hpp"

namespace cpp_redis
{
	class hash_client :public client {
	public:
		hash_client() = default;
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
			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_){
				return 0;
			}

			const auto results = res->get_int_results();
			if (results.empty()){
				return 0;
			}

			return results[0];
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
			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();
			if (results.empty()) {
				return 0;
			}

			return results[0];
		}

		virtual int hash_exists(std::string&& key, std::string&& field)
		{
			check_args();
			std::string msg = request_->req_n_key(request_->get_cmd(redis_cmd::hash_exists), std::forward<std::string>(key),
				std::forward<std::string>(field));

			socket_->send_msg(std::move(msg));
			const auto res = socket_->get_responese();
			if (res->get_result_code() != status::int_result_) {
				return 0;
			}

			const auto results = res->get_int_results();
			if (results.empty()) {
				return 0;
			}

			return results[0];
		}

	};
}

#endif // cpp_hash_client_h__

#ifndef client_h__
#define client_h__

#include "cpp_redis_list.hpp"
#include "cpp_redis_string.hpp"
#include "cpp_set_client.hpp"
#include "cpp_hash_client.hpp"
#include "cpp_zset_client.hpp"

namespace cpp_redis {
	template<typename type >
	class redis_client
	{
	public:
		redis_client() {
#if (_MSC_VER >= 1700 && _MSC_VER <= 1900) //vs2012-vs2015
			if (constexpr (is_sting_)) {
				request_type_ = request_type::string_request;
			}
			else if (constexpr (is_list_)) {
				request_type_ = request_type::list_request;
			}
			else if (constexpr (is_set_)) {
				request_type_ = request_type::set_request;
			}
			else if (constexpr (is_zset)) {
				request_type_ = request_type::zset_request;
			}
			else if (constexpr (is_hash)) {
				request_type_ = request_type::hash_request;
			}
			else if (constexpr(is_none)) {
				request_type_ = request_type_::none;
			}
#else
			if constexpr (is_sting_) {
				request_type_ = request_type::string_request;
			}
			else if constexpr (is_list_) {
				request_type_ = request_type::list_request;
			}
			else if constexpr (is_set_) {
				request_type_ = request_type::set_request;
			}
			else if constexpr (is_zset) {
				request_type_ = request_type::zset_request;
			}
			else if constexpr (is_hash) {
				request_type_ = request_type::hash_request;
			}
			else if constexpr (is_none) {
				request_type_ = request_type_::none;
			}
#endif
			create_object();
		}

		~redis_client() = default;

		std::string get_current_error() {
			if (client_ == nullptr) {
				return "";
			}

			return client_->get_current_error();
		}

		bool set_db_num(int&& num)
		{
			if (client_ == nullptr) {
				return false;
			}

			return client_->set_db_num(std::forward<int>(num));
		}

		bool auth(std::string&& password)
		{
			if (client_ == nullptr) {
				return false;
			}

			return client_->auth(std::forward<std::string>(password));
		}

		template<typename...Args>
		constexpr bool connect_to(std::string&& ip, Args&&...args) {
			if (client_ == nullptr) {
				return false;
			}

			return client_->connect_to(std::forward<std::string>(ip), std::forward<Args>(args)...);
		}

		bool delete_key(std::string&& key)
		{
			if (client_ == nullptr) {
				return false;
			}

			return client_->delete_key(std::forward<std::string>(key));
		}

		bool is_key_exist(std::string&& key)
		{
			if (client_ == nullptr) {
				return false;
			}

			return client_->is_key_exist(std::forward<std::string>(key));
		}

		bool expire(std::string&& key, std::size_t seconds)
		{
			if (client_ == nullptr) {
				return false;
			}

			return client_->expire(std::forward<std::string>(key), seconds);
		}

		bool expire_at(std::string&& key, std::size_t unix_timestamp)
		{
			if (client_ == nullptr) {
				return false;
			}

			return client_->expire_at(std::forward<std::string>(key), unix_timestamp);
		}

		int  remainder_ttl(std::string&& key)
		{
			if (client_ == nullptr) {
				return INT32_MAX;
			}

			return client_->remainder_ttl(std::forward<std::string>(key));
		}

		bool setex(std::string&& key, std::string&& value, size_t seconds)
		{
			static_assert(is_sting_, "This API Support String Request");

			if (client_ == nullptr) {
				return false;
			}

			return client_->setex(std::forward<std::string>(key), std::forward<std::string>(value), seconds);
		}

		bool set(std::string&& key, std::string&& value)
		{
			static_assert(is_sting_, "This API Support String Request");
			if (client_ == nullptr) {
				return false;
			}

			return client_->set(std::forward<std::string>(key), std::forward<std::string>(value));
		}

		std::tuple<bool, int> incr(std::string&& key, int increment = 1)
		{
			static_assert(is_sting_, "This API Support String Request");
			if (client_ == nullptr) {
				return { false,-1 };
			}

			return client_->incr(std::forward<std::string>(key), increment);
		}

		std::tuple<bool, int> decr(std::string&& key, int increment = 1)
		{
			static_assert(is_sting_, "This API Support String Request");
			if (client_ == nullptr) {
				return { false,-1 };
			}

			return client_->decr(std::forward<std::string>(key), increment);
		}

		std::string get_reflect_value(std::string&& key)
		{
			static_assert(is_sting_, "This API Support String Request");
			if (client_ == nullptr) {
				return "";
			}

			return client_->get_reflect_value(std::forward<std::string>(key));
		}

		std::string get_set_key(std::string&& key, std::string&& value)
		{
			static_assert(is_sting_, "This API Support String Request");
			if (client_ == nullptr) {
				return "";
			}

			return client_->get_set_key(std::forward<std::string>(key), std::forward<std::string>(value));
		}

		std::string substr_reflect_value(std::string&& key, int start, int end)
		{
			static_assert(is_sting_, "This API Support String Request");
			if (client_ == nullptr) {
				return "";
			}

			return client_->substr_reflect_value(std::forward<std::string>(key), start, end);
		}

		template<typename...Args>
		VALUES multi_get_keys(Args&&...key)
		{
			static_assert(is_sting_, "This API Support String Request");
			auto ptr = std::dynamic_pointer_cast<string_client>(client_);
			if (ptr == nullptr) {
				return{};
			}

			return ptr->multi_get_keys(std::forward<Args>(key)...);
		}

		template<typename...Args>
		bool multi_set_keys(Args&&...key_value)
		{
			static_assert(is_sting_, "This API Support String Request");
			auto ptr = std::dynamic_pointer_cast<string_client>(client_);
			if (ptr == nullptr) {
				return{};
			}

			return ptr->multi_set_keys(std::forward<Args>(key_value)...);
		}

		template<typename...Args>
		int multi_set_if_not_set(Args...key_value)
		{
			static_assert(is_sting_, "This API Support String Request");
			auto ptr = std::dynamic_pointer_cast<string_client>(client_);
			if (ptr == nullptr) {
				return{};
			}

			return ptr->multi_set_if_not_set(std::forward<Args>(key_value)...);
		}

		std::tuple<bool, int> append_value(std::string&& key, std::string&& new_value)
		{
			static_assert(is_sting_, "This API Support String Request");
			if (client_ == nullptr) {
				return { false,-1 };
			}

			return client_->append_value(std::forward<std::string>(key), std::forward<std::string>(new_value));
		}

		std::tuple<bool, int> list_rpush(std::string&& key, std::string&& value)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return { false,-1 };
			}

			return client_->list_rpush(std::forward<std::string>(key), std::forward<std::string>(value));
		}

		std::tuple<bool, int> list_rpush_if(std::string&& key, std::string&& value)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return { false,-1 };
			}

			return client_->list_rpush_if(std::forward<std::string>(key), std::forward<std::string>(value));
		}

		std::tuple<bool, int> list_lpush(std::string&& key, std::string&& value)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return { false,-1 };
			}

			return client_->list_lpush(std::forward<std::string>(key), std::forward<std::string>(value));
		}

		std::tuple<bool, int> list_lpush_if(std::string&& key, std::string&& value)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return { false,-1 };
			}

			return client_->list_lpush_if(std::forward<std::string>(key), std::forward<std::string>(value));
		}

		int32_t list_size(std::string&& key)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return INT32_MAX;
			}

			return client_->list_size(std::forward<std::string>(key));
		}

		RESULTS_TYPE list_range(std::string&& key, int start, int end)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return {};
			}

			return client_->list_range(std::forward<std::string>(key), start, end);
		}

		std::string list_lpop(std::string&& key)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return "";
			}

			return client_->list_lpop(std::forward<std::string>(key));
		}

		std::string list_rpop(std::string&& key)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return "";
			}

			return client_->list_rpop(std::forward<std::string>(key));
		}

		std::string list_brpop(std::string&& key, size_t timeout = 0)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return "";
			}

			return client_->list_brpop(std::forward<std::string>(key), timeout);
		}

		std::string list_blpop(std::string&& key, size_t timeout = 0)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return "";
			}

			return  client_->list_blpop(std::forward<std::string>(key), timeout);
		}

		bool list_trim(std::string&& key, int start, int end)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return "";
			}

			return client_->list_trim(std::forward<std::string>(key), start, end);
		}

		std::string list_index(std::string&& key, int index)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return "";
			}

			return client_->list_index(std::forward<std::string>(key), index);
		}

		bool list_set(std::string&& key, std::string&& value, int index)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return false;
			}

			return client_->list_set(std::forward<std::string>(key), std::forward<std::string>(value), index);
		}

		std::tuple<bool, int> list_del_elem(std::string&& key, std::string&& value, int index = 0)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return { false,-1 };
			}

			return client_->list_del_elem(std::forward<std::string>(key), std::forward<std::string>(value), index);
		}

		std::string list_rpoplpush(std::string&& src_key, std::string&& dst_key)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return "";
			}

			return client_->list_rpoplpush(std::forward<std::string>(src_key), std::forward<std::string>(dst_key));
		}

		std::string list_brpoplpush(std::string&& src_key, std::string&& dst_key, int timeout = 0)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return "";
			}

			return client_->list_brpoplpush(std::forward<std::string>(src_key), std::forward<std::string>(dst_key), timeout);
		}

		int list_insert_before(std::string&& key, std::string&& dst_value, std::string&& insert_value)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return INT32_MAX;
			}

			return client_->list_insert_before(std::forward<std::string>(key),
				std::forward<std::string>(dst_value), std::forward<std::string>(insert_value));
		}

		int list_insert_after(std::string&& key, std::string&& dst_value, std::string&& insert_value)
		{
			static_assert(is_list_, "This API Support List Request");

			if (client_ == nullptr) {
				return INT32_MAX;
			}

			return client_->list_insert_after(std::forward<std::string>(key),
				std::forward<std::string>(dst_value), std::forward<std::string>(insert_value));
		}

		template<typename...Args>
		std::tuple<bool, int>set_add(std::string&& key, Args&&...args)
		{
			static_assert(is_set_, "This API Support Set Request");
			auto ptr = std::dynamic_pointer_cast<set_client>(client_);
			if (ptr == nullptr) {
				return { false,-1 };
			}

			return ptr->set_add(std::forward<std::string>(key), std::forward<Args>(args)...);
		}

		template<typename...Args>
		std::tuple<bool, int>set_delete_elem(std::string&& key, Args&&...args)
		{
			static_assert(is_set_, "This API Support Set Request");
			auto ptr = std::dynamic_pointer_cast<set_client>(client_);
			if (ptr == nullptr) {
				return { false,-1 };
			}

			return ptr->set_delete_elem(std::forward<std::string>(key), std::forward<Args>(args)...);
		}

		bool set_is_member(std::string&& key, std::string&& value)
		{
			static_assert(is_set_, "This API Support Set Request");
			if (client_ == nullptr) {
				return false;
			}

			return client_->set_is_member(std::forward<std::string>(key), std::forward<std::string>(value));
		}

		std::string set_rdel_elem(std::string&& key)
		{
			static_assert(is_set_, "This API Support Set Request");
			if (client_ == nullptr) {
				return "";
			}

			return client_->set_rdel_elem(std::forward<std::string>(key));
		}

		//ֻ����������ᷢ��ɾ��
		RESULTS_TYPE set_rand_elem(std::string&& key, int count)
		{
			static_assert(is_set_, "This API Support Set Request");
			if (client_ == nullptr) {
				return {};
			}

			return client_->set_rand_elem(std::forward<std::string>(key), count);
		}

		bool set_move_elem(std::string&& src_key, std::string&& dst_key, std::string&& member)
		{
			static_assert(is_set_, "This API Support Set Request");
			if (client_ == nullptr) {
				return false;
			}

			return client_->set_move_elem(std::forward<std::string>(src_key),
				std::forward<std::string>(dst_key), std::forward<std::string>(member));
		}

		size_t set_get_size(std::string&& key)
		{
			static_assert(is_set_, "This API Support Set Request");
			if (client_ == nullptr) {
				return 0;

			}
			return  client_->set_get_size(std::forward<std::string>(key));
		}

		RESULTS_TYPE set_get_all_member(std::string&& key)
		{
			static_assert(is_set_, "This API Support Set Request");
			if (client_ == nullptr) {
				return {};

			}

			return  client_->set_get_all_member(std::forward<std::string>(key));
		}

		//�󼯺ϵĽ��������һ��Ϊ�գ��ͷ��ؿ�
		template<typename...Args>
		RESULTS_TYPE set_sinter(Args&&...keys)
		{
			static_assert(is_set_, "This API Support Set Request");
			auto ptr = std::dynamic_pointer_cast<set_client>(client_);
			if (ptr == nullptr) {
				return {};
			}

			return ptr->set_sinter(std::forward<Args>(keys)...);
		}

		//�󼯺ϵĽ��������һ��Ϊ�գ��ͷ��ؿ�,����������һ���ط�
		template<typename...Args>
		int set_inter_store(std::string&& dst_key, Args&&...keys)
		{
			static_assert(is_set_, "This API Support Set Request");
			auto ptr = std::dynamic_pointer_cast<set_client>(client_);
			if (ptr == nullptr) {
				return -1;
			}

			return ptr->set_inter_store(std::forward<std::string>(dst_key), std::forward<Args>(keys)...);
		}

		//�󼯺ϵĲ�����,������key����Ϊ�� 
		//(����һ�����ϵ�ȫ����Ա���ü��������и������ϵĲ���)
		template<typename...Args>
		RESULTS_TYPE set_union(Args&&...key)
		{
			static_assert(is_set_, "This API Support Set Request");
			auto ptr = std::dynamic_pointer_cast<set_client>(client_);
			if (ptr == nullptr) {
				return {};
			}

			return ptr->set_union(std::forward<Args>(key)...);
		}
		//�󼯺ϵĲ��������һ��Ϊ�գ��ͷ��ؿ�,����������һ���ط�
		//(����һ�����ϵ�ȫ����Ա���ü��������и������ϵĲ���)
		template<typename...Args>
		int set_union_store(std::string&& dst_key, Args&&...keys)
		{
			static_assert(is_set_, "This API Support Set Request");
			auto ptr = std::dynamic_pointer_cast<set_client>(client_);
			if (ptr == nullptr) {
				return -1;
			}

			return ptr->set_union_store(std::forward<std::string>(dst_key), std::forward<Args>(keys)...);
		}

		//����һ�����ϵ�ȫ����Ա���ü��������и�������֮��Ĳ��
		//�����ڵ� key ����Ϊ�ռ���
		template<typename...Args>
		RESULTS_TYPE set_diff(Args&&...key)
		{
			static_assert(is_set_, "This API Support Set Request");
			auto ptr = std::dynamic_pointer_cast<set_client>(client_);
			if (ptr == nullptr) {
				return{};
			}

			return ptr->set_diff(std::forward<Args>(key)...);
		}

		template<typename...Args>
		int set_diff_store(std::string&& dst_key, Args&&...key)
		{
			static_assert(is_set_, "This API Support Set Request");
			auto ptr = std::dynamic_pointer_cast<set_client>(client_);
			if (ptr == nullptr) {
				return -1;
			}

			return ptr->set_diff_store(std::forward<std::string>(dst_key), std::forward<Args>(key)...);
		}

		//ZADD key score member [[score member] [score member] ��]
		template<typename...Args>
		int zset_add(std::string&& key, Args&&...args) {
			constexpr auto Size = sizeof...(args)+1;
			static_assert(is_zset, "This API Support ZSet Request");

			keys_.push_back(std::forward<std::string>(key));
			make_keys(std::forward<Args>(args)...);

			if (keys_.size() == 1 || keys_.size()!= Size) {
				return false;
			}

			return client_->zset_add(std::forward<std::string>(key),std::move(keys_));
		}

		//��ȡָ��zset��Ա��ֵ
		template<typename T>
		std::string zset_score(std::string&& key, T&& member)
		{
			check_pass_args(std::forward<T>(member));
			static_assert(is_zset, "This API Support ZSet Request");

			std::string value;
#if (_MSC_VER >= 1700 && _MSC_VER <= 1900) //vs2012-vs2015
			if (constexpr (std::is_same<T, float>::value)) {
				value = cpp_redis::unit::float_to_string(member);
			}
			else if  constexpr (cpp_redis::traits::is_string<T>::value) {
				value = buid_string(member);
			}
			else if (constexpr(std::is_same<T, int>::value)) {
				value = cpp_redis::unit::int_to_string(member);
			}
#else
			if constexpr (std::is_same<T, float>::value) {
				value = cpp_redis::unit::float_to_string(member);
			}
			else if constexpr (std::is_same<T, double>::value) {
				value = cpp_redis::unit::double_to_string(member);
			}
			else if  constexpr (cpp_redis::traits::is_string<T>::value) {
				value = buid_string(member);
			}
			else if constexpr (std::is_same<T, int>::value) {
				value = cpp_redis::unit::int_to_string(member);
			}

			return client_->zset_score(std::forward<std::string>(key), std::move(value));
#endif
		}

		//��ȡָ��zset��Ա����ֵ
		//member:�������ݿ��е�value�ֶ�
		template<typename T>
		std::string zset_incrby(std::string&& key, int increment, T&& member)
		{
			check_pass_args(std::forward<T>(member));
			static_assert(is_zset, "This API Support ZSet Request");

			std::string value;
#if (_MSC_VER >= 1700 && _MSC_VER <= 1900) //vs2012-vs2015
			if (constexpr (std::is_same<T, float>::value)) {
				value = cpp_redis::unit::float_to_string(member);
			}
			else if  constexpr (cpp_redis::traits::is_string<T>::value) {
				value = buid_string(member);
			}
			else if (constexpr(std::is_same<T, int>::value)) {
				value = cpp_redis::unit::int_to_string(member);
			}
#else
			if constexpr (std::is_same<T, float>::value) {
				value = cpp_redis::unit::float_to_string(member);
			}
			else if constexpr (std::is_same<T, double>::value) {
				value = cpp_redis::unit::double_to_string(member);
			}
			else if  constexpr (cpp_redis::traits::is_string<T>::value) {
				value = buid_string(member);
			}
			else if constexpr (std::is_same<T, int>::value) {
				value = cpp_redis::unit::int_to_string(member);
			}

			return client_->zset_incrby(std::forward<std::string>(key), unit::int_to_string(increment), std::move(value));
#endif
		}

		//�������� key������
		int zset_counts(std::string&& key)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_card(std::forward<std::string>(key));
		}

		//�������� key�� min��max��������
		int zset_range_counts(std::string&& key, int min, int max)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_count(std::forward<std::string>(key), unit::int_to_string(min), unit::int_to_string(max));
		}

		//�����б��� value1, score1, ..., valueN, scoreN �ĸ�ʽ��ʾ��
		//with_scores:false����score����
		//��������
		RESULTS_TYPE zset_range(std::string&& key, int begin, int end, bool with_scores = true)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_range(std::forward<std::string>(key), unit::int_to_string(begin), unit::int_to_string(end), with_scores);
		}

		//���г�Ա��λ�ð� score ֵ�ݼ�(�Ӵ�С)������,�����zrange����
		//�ݼ�����
		//�ֵ��������
		RESULTS_TYPE zset_rerange(std::string&& key, int begin, int end, bool with_scores = true)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_revrange(std::forward<std::string>(key), unit::int_to_string(begin), unit::int_to_string(end), with_scores);
		}

		//�������ڵ�score����
		RESULTS_TYPE zset_range_score(std::string&& key, int min, int max,
			bool with_scores = true, bool limit = false, int limit_min = 0, int limit_max = 1)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_range_score(std::forward<std::string>(key), unit::int_to_string(min),
				unit::int_to_string(max), with_scores, limit, unit::int_to_string(limit_min), unit::int_to_string(limit_max));
		}

		//�������ڵ�score�����ݿ�������ȡֵ������
		RESULTS_TYPE zset_revrange_score(std::string&& key, int max, int min,
			bool with_scores = true, bool limit = false, int limit_min = 0, int limit_max = 1)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_revrange_score(std::forward<std::string>(key), unit::int_to_string(max),
				unit::int_to_string(min), with_scores, limit, unit::int_to_string(limit_min), unit::int_to_string(limit_max));
		}

		//���򣬴�0��ʼ
		int zset_rank(std::string&& key, std::string&& member)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_rank(std::forward<std::string>(key), std::forward<std::string>(member));
		}

		//���򣬴�0��ʼ�����Ӵ�Ŀ�ʼ��
		int zset_revrank(std::string&& key, std::string&& member)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_revrank(std::forward<std::string>(key), std::forward<std::string>(member));
		}

		//ZREM key score member [[score member][score member] ��]
		template<typename...Args>
		bool zset_rem(std::string&& key, Args&&...args)
		{
			constexpr auto Size = sizeof...(args) + 1;
			static_assert(is_zset, "This API Support ZSet Request");
			auto ptr = std::dynamic_pointer_cast<zset_client>(client_);
			if (ptr == nullptr) {
				return false;
			}

			keys_.push_back(std::forward<std::string>(key));
			make_keys(std::forward<Args>(args)...);

			if (keys_.size() ==1 || keys_.size() !=Size){
				return false;
			}

			return ptr->zset_rem(std::forward<std::string>(key),std::move(keys_));
		}

		//�Ƴ����� key �У�ָ������(rank)�����ڵ����г�Ա
		int zset_remrangeby_rank(std::string&& key,int begin,int end)
		{
			static_assert(is_zset, "This API Support ZSet Request");

			return client_->zset_remrangeby_rank(std::forward<std::string>(key), unit::int_to_string(begin), unit::int_to_string(end));
		}

		//�Ƴ����� key �У����� score ֵ���� min �� max ֮��(�������� min �� max )�ĳ�Ա��
		int zset_remrangebyscore(std::string&& key,int min,int max)
		{
			static_assert(is_zset, "This API Support ZSet Request");
			return client_->zset_remrangebyscore(std::forward<std::string>(key), unit::int_to_string(min), unit::int_to_string(max));
		}
		
		//�Ϸ��� min �� max �����������(����[�� ����(��ʾ�����䣨ָ����ֵ���ᱻ�����ڷ�Χ֮�ڣ��� ��[���ʾ�����䣨ָ����ֵ�ᱻ�����ڷ�Χ֮�ڣ���
		//����ֵ + �� - �� min �����Լ� max �����о�����������壬 ���� + ��ʾ�����ޣ� �� - ��ʾ�����ޡ� 
		//��ˣ� ��һ�����г�Ա�ķ�ֵ����ͬ�����򼯺Ϸ������� ZRANGEBYLEX <zset> -+�� ����������򼯺��е�����Ԫ�ء�

		RESULTS_TYPE zset_rangebylex(std::string&& key,std::string&&min,std::string&& max,bool limit=false,int limit_min=0,int limit_max=1)
		{
			static_assert(is_zset, "This API Support ZSet Request");
			return client_->zset_rangebylex(std::forward<std::string>(key),std::forward<std::string>(min),std::forward<std::string>(max), 
				limit,unit::int_to_string(limit_max),unit::int_to_string(limit_max));
		}

		//�˽ӿں�����ӿ�һ����ֻ�Ƿ�������
		int zset_lexcount(std::string&& key, std::string&& min, std::string&& max)
		{
			static_assert(is_zset, "This API Support ZSet Request");
			return client_->zset_lexcount(std::forward<std::string>(key), std::forward<std::string>(min), std::forward<std::string>(max));
		}

		//������ţ�ɾ��Ԫ��
		int zset_remrangebylex(std::string&& key, std::string&& min, std::string&& max)
		{
			static_assert(is_zset, "This API Support ZSet Request");
			return client_->zset_remrangebylex(std::forward<std::string>(key),std::forward<std::string>(min), std::forward<std::string>(max));
		}
		
		//���������һ���������򼯵Ĳ��������и��� key ������������ num_keys ����ָ����
		//�����ò���(�����)���浽 dst_store_key ,����num_keys,�������key�ĸ���
		//Ĭ������£��������ĳ����Ա�� score ֵ�����и������¸ó�Ա score ֵ֮ ��
		//����ʹ�ý��ܣ�����1��Ŀ��洢��key,���� 2����͵ķ�ʽ������3��N��key ����Ȩ��,����ʹ�ÿ��Կ��ٷ�����
		template<typename...Args>
		int zset_union_store(std::string&& dst_store_key,int num_keys,aggregate_mothod mothod,
			int weight_min,int weight_max,Args&&...args)
		{
			constexpr auto Size = sizeof...(args) + 2;
			static_assert(is_zset, "This API Support ZSet Request");

			keys_.push_back(std::forward<std::string>(dst_store_key));
			keys_.emplace_back(unit::int_to_string(num_keys));

			make_keys(std::forward<Args>(args)...);

			if (keys_.size() == 1 || keys_.size() != Size) {
				return false;
			}

			keys_.emplace_back("WEIGHTS");
			keys_.emplace_back(unit::int_to_string(weight_min));
			keys_.emplace_back(unit::int_to_string(weight_max));
			return client_->zset_union_store(std::move(keys_), mothod);
		}

		//�󽻼�������������Բο� zset_union_store�ӿ�
		template<typename...Args>
		int zset_inter_store(std::string&& dst_store_key, int num_keys, aggregate_mothod mothod,
			int weight_min, int weight_max, Args&&...args)
		{
			constexpr auto Size = sizeof...(args) + 2;
			static_assert(is_zset, "This API Support ZSet Request");

			keys_.push_back(std::forward<std::string>(dst_store_key));
			keys_.emplace_back(unit::int_to_string(num_keys));

			make_keys(std::forward<Args>(args)...);

			if (keys_.size() == 1 || keys_.size() != Size) {
				return false;
			}

			keys_.emplace_back("WEIGHTS");
			keys_.emplace_back(unit::int_to_string(weight_min));
			keys_.emplace_back(unit::int_to_string(weight_max));
			return client_->zset_inter_store(std::move(keys_), mothod);
		}

	private:
		void make_keys()
		{

		}

		template<typename T,typename...Args>
		void make_keys(T&&header,Args&&...args)
		{
			std::string value;
#if (_MSC_VER >= 1700 && _MSC_VER <= 1900) //vs2012-vs2015
			if (constexpr (std::is_same<T, float>::value)) {
				value = cpp_redis::unit::float_to_string(header);
			}
			else if  constexpr (cpp_redis::traits::is_string<T>::value) {
				value = buid_string(header);
			}
			else if (constexpr(std::is_same<T, int>::value)) {
				value = cpp_redis::unit::int_to_string(header);
			}
#else
			if constexpr (std::is_same<T, float>::value) {
				value = cpp_redis::unit::float_to_string(header);
			}
			else if constexpr (std::is_same<T, double>::value) {
				value = cpp_redis::unit::double_to_string(header);
			}
			else if  constexpr (cpp_redis::traits::is_string<T>::value) {
				value = buid_string(header);
			}
			else if constexpr (std::is_same<T, int>::value) {
				value = cpp_redis::unit::int_to_string(header);
			}

			if (!value.empty()){
				keys_.push_back(std::move(value));
			}

			make_keys(std::forward<Args>(args)...);
#endif
		}

		void create_object()
		{
			if (request_type_ == cpp_redis::string_request) {
				client_ = std::make_shared<string_client>();
			}
			else if (request_type_ == cpp_redis::list_request) {
				client_ = std::make_shared<list_client>();
			}
			else if (request_type_ == cpp_redis::set_request) {
				client_ = std::make_shared<set_client>();
			}
			else if (request_type_ == cpp_redis::zset_request) {
				client_ = std::make_shared<zset_client>();
			}
			else if (request_type_ == cpp_redis::hash_request) {
				client_ = std::make_shared<hash_client>();
			}
			else {
				static_assert(is_none, "Please pass String List set_request Set Hash");
			}
		}

		template<typename T>
		std::string buid_string(T&& value)
		{
			constexpr bool is_string = cpp_redis::traits::is_string<T>::value;
			static_assert(is_string, "T only string ");

			std::string str;

#if (_MSC_VER >= 1700 && _MSC_VER <= 1900) //vs2012-vs2015
			if (constexpr (std::is_same<char*, typename std::decay<T>::type>::value)) {
				size_t size = strlen(value);
				str.resize(size);
				std::copy(value, value + size, str.begin());
			}
			else if (constexpr (std::is_same<const char*, typename std::decay<T>::type>::value)) {
				size_t size = strlen(value);
				str.resize(size);
				std::copy(value, value + size, str.begin());
			}
			else {
				str = std::move(value);
			}
#else
			if constexpr (std::is_same<char*, typename std::decay<T>::type>::value) {
				size_t size = strlen(value);
				str.resize(size);
				memcpy(&str[0], value, size);
			}
			else if constexpr (std::is_same<const char*, typename std::decay<T>::type>::value) {
				size_t size = strlen(value);
				str.resize(size);
				memcpy(&str[0], value, size);
			}
			else {
				str = std::move(value);
			}
#endif
			return std::move(str);
		}

		template<typename T>
		void check_pass_args(T&& value)
		{
#if (_MSC_VER >= 1700 && _MSC_VER <= 1900) //vs2012-vs2015
			if (constexpr (cpp_redis::traits::is_string<T>::value))) {
			constexpr bool is_string = cpp_redis::traits::is_string<T>::value;
			static_assert(is_string, "T only support double string float int ");
			}
			else {
				constexpr bool is_none = cpp_redis::traits::contains<T, double, float, int>::value;
				static_assert(is_none, "T only support double string float int ");
			}
#else
			if constexpr (cpp_redis::traits::is_string<T>::value) {
				constexpr bool is_string = cpp_redis::traits::is_string<T>::value;
				static_assert(is_string, "T only support double string float int ");
			}
			else {
				constexpr bool is_none = cpp_redis::traits::contains<T, double, float, int>::value;
				static_assert(is_none, "T only support double string float int ");
			}
#endif
		}
	private:
		static constexpr bool is_sting_ = std::is_same<type, String>::value;
		static constexpr bool is_list_ = std::is_same<type, List>::value;
		static constexpr bool is_set_ = std::is_same<type, Set>::value;
		static constexpr bool is_zset = std::is_same<type, ZSet>::value;
		static constexpr bool is_hash = std::is_same<type, Hash>::value;
		static constexpr bool is_none = cpp_redis::traits::contains<type, String, List, Set, ZSet, Hash>::value;
		int request_type_ = request_type::none;
		std::shared_ptr<client>client_;
		std::vector<std::string>keys_;
	};
}
#endif // client_h__

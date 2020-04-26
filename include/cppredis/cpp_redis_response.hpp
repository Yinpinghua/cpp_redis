#ifndef cpp_redis_response_h__
#define cpp_redis_response_h__

#include "cpp_define.h"

namespace cpp_redis {
	class cpp_redis_response {
	public:
		void reset()
		{
			err_.clear();
			status_.clear();
			results_.clear();
			int_results_.clear();
			result_code_ = 0;
		}

		void set_result_code(int result_code)
		{
			result_code_ = result_code;
		}

		int get_result_code()const 
		{
			return result_code_;
		}

		void set_error(std::string &&error) 
		{
			err_ = std::move(error);
		}

		std::string get_error()
		{
			return std::move(err_);
		}

		void set_int_results(int value)
		{
			int_results_.emplace_back(value);
		}

		std::vector<int> get_int_results()
		{
			return std::move(int_results_);
		}

		void set_results(std::string &&value)
		{
			results_.emplace_back(value);
		}

		std::vector<std::string> get_results()
		{
			return std::move(results_);
		}

		void set_status(std::string&& status)
		{
			status_ = std::move(status);
		}

		std::string get_status()
		{
			return std::move(status_);
		}
	private:
		int result_code_; //-1: unconnected, 0: results_; 2: int ; 4: err_;  8: status_
		std::string err_;
		std::string status_;
		std::vector<int> int_results_;
		std::vector<std::string> results_;
	};
}
#endif // cpp_redis_response_h__

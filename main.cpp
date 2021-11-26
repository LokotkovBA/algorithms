#include <iostream>
#include <vector>
#include <unordered_map>

namespace algos
{
	std::vector<int> twoSum(std::vector<int>& nums, int target)
	{
		std::unordered_map<int, int> divs;
		std::vector<int> output(2, -1);
		int size = nums.size();
		for (int i = 0; i < size; i++)
		{
			int curDiv = target - nums[i];
			if (divs.find(nums[i]) == divs.end())
				divs[curDiv] = i;
			else
			{
				output = { divs[nums[i]], i  };
				return output;
			}
		}
		return output;
	}

	std::vector<int>* howSumBF(std::vector<int>& nums, int target)
	{
		if (target == 0)
		{
			std::vector<int>* result = new std::vector<int>;
			return result;
		}
		if (target < 0)
			return nullptr;
		for (int i = 0; i < nums.size(); i++)
		{
			int div = target - nums[i];
			std::vector<int>* result = howSumBF(nums, div);
			if (result != nullptr)
			{
				result->push_back(nums[i]);
				return result;
			}
		}
		return nullptr;
	}

	std::vector<int>* howSumDP(std::vector<int>& nums, int target, std::unordered_map<int, std::vector<int>*>& mem)
	{
		if (mem.find(target) != mem.end())
			return mem[target];
		if (target == 0)
		{
			std::vector<int>* result = new std::vector<int>;
			return result;
		}
		if (target < 0)
			return nullptr;
		for (int i = 0; i < nums.size(); i++)
		{
			int div = target - nums[i];
			std::vector<int>* result = howSumDP(nums, div, mem);
			if (result != nullptr)
			{
				result->push_back(nums[i]);
				mem[target] = result;
				return result;
			}
		}
		mem[target] = nullptr;
		return nullptr;
	}

	void log(std::vector<int>* inp)
	{
		if (inp != nullptr)
			for (int i = 0; i < inp->size(); i++)
				std::cout << (*inp)[i] << ", ";
		else
			std::cout << "nullptr";
		std::cout << std::endl;
	}

	std::vector<int>* bestSumBF(std::vector<int>& nums, int target)
	{
		if (target == 0)
		{
			std::vector<int>* result = new std::vector<int>;
			return result;
		}
		if (target < 0)
			return nullptr;

		std::vector<int>* shortestCombination = nullptr;

		for (int num : nums)
		{
			int remain = target - num;
			std::vector<int>* remainComb = bestSumBF(nums, remain);
			if (remainComb != nullptr)
			{
				remainComb->push_back(num);
				if (shortestCombination == nullptr || remainComb->size() < shortestCombination->size())
					shortestCombination = remainComb;
			}
		}

		return shortestCombination;
	}

	std::vector<int>* bestSumDP(std::vector<int>& nums, int target, std::unordered_map<int, std::vector<int>*>& mem)
	{
		if (mem.find(target) != mem.end())
			return mem[target];
		if (target == 0)
		{
			std::vector<int>* result = new std::vector<int>;
			return result;
		}
		if (target < 0)
			return nullptr;

		std::vector<int>* shortestCombination = nullptr;

		for (int num : nums)
		{
			int remain = target - num;
			std::vector<int>* remainComb = bestSumDP(nums, remain, mem);
			if (remainComb != nullptr)
			{
				int newSize = remainComb->size();
				std::vector<int>* combination = new std::vector<int>(newSize + 1);
				for (int i = 0; i < newSize; i++)
					combination->operator[](i) = remainComb->operator[](i);
				combination->operator[](newSize) = num;

				if (shortestCombination == nullptr || combination->size() < shortestCombination->size())
					shortestCombination = combination;
			}
		}

		mem[target] = shortestCombination;
		return shortestCombination;
	}

	bool canConstruct(std::vector<std::string>& words, std::string& target, std::shared_ptr<std::unordered_map<std::string, bool>> mem = std::make_shared<std::unordered_map<std::string, bool>>())
	{
		if (mem->find(target) != mem->end())
			return (*mem)[target];
		if (target == "")
			return true;

		for (int i = 0; i < words.size(); i++)
		{
			if (target.find(words[i]) == 0)
			{
				std::string suffix = target.substr(words[i].size());
				if (canConstruct(words, suffix, mem))
				{
					mem->insert({ target, true });
					return true;
				}
			}

		}

		mem->insert({ target, false });
		return false;
	}

	int countConstruct(std::vector<std::string>& words, std::string& target, std::shared_ptr<std::unordered_map<std::string, int>> mem = std::make_shared<std::unordered_map<std::string, int>>())
	{
		if(mem->find(target) != mem->end())
			return (*mem)[target];
		if (target == "")
			return 1;

		int totalCount = 0;
		for (int i = 0; i < words.size(); i++)
		{
			if (target.find(words[i]) == 0)
			{
				std::string suffix = target.substr(words[i].size());
				int numWaysForRest = countConstruct(words, suffix, mem);
				totalCount += numWaysForRest;
			}
		}

		mem->insert({ target, totalCount });
		return totalCount;
	}
}

void main()
{
	
	std::vector<std::string> words = { "ab", "abc", "cd", "def", "abcd"};
	std::string input_word = "abcdef";
	std::cout << algos::countConstruct(words, input_word) << std::endl;

	words = { "purp", "p", "ur", "le", "purpl" };
	input_word = "purple";
	std::cout << algos::countConstruct(words, input_word) << std::endl;

	words = { "bo", "rd", "ate", "t", "ska", "sk", "boar"};
	input_word = "skateboard";
	std::cout << algos::countConstruct(words, input_word) << std::endl;

	words = { "a", "p", "ent", "enter", "ot", "o", "t"};
	input_word = "enterapotentpot";
	std::cout << algos::countConstruct(words, input_word) << std::endl;

	words = { "e", "eee", "eeee", "eeeee", "eeeeeeee" };
	input_word = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
	std::cout << algos::countConstruct(words, input_word) << std::endl;
	
}
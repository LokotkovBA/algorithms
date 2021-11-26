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
}

void main()
{
	std::unordered_map<int, std::vector<int>*> mems;
	std::vector<int> nums = { 2,3 };
	//algos::log(algos::bestSumBF(nums, 7));
	algos::log(algos::bestSumDP(nums, 7, mems));
	mems.clear();

	nums = { 5,3,4,7 };
	//algos::log(algos::bestSumBF(nums, 7));
	algos::log(algos::bestSumDP(nums, 7, mems));
	mems.clear();

	nums = { 1, 4, 5};
	//algos::log(algos::bestSumBF(nums, 8));
	algos::log(algos::bestSumDP(nums, 8, mems));
	mems.clear();

	nums = { 2,3,5 };
	//algos::log(algos::bestSumBF(nums, 8));
	algos::log(algos::bestSumDP(nums, 8, mems));
	mems.clear();

	nums = {1, 2, 5, 25};
	//algos::log(algos::bestSumBF(nums, 100));
	algos::log(algos::bestSumDP(nums, 100, mems));
	mems.clear();
}
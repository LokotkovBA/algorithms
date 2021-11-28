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

	std::shared_ptr<std::vector<std::vector<std::string>>> allCounstruct(std::vector<std::string>& words, std::string& target, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::vector<std::vector<std::string>>>>> mem = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<std::vector<std::string>>>>>())
	{
		if (mem->find(target) != mem->end())
			return (*mem)[target];
		if (target == "")
		{
			std::shared_ptr<std::vector<std::vector<std::string>>> output = std::make_shared<std::vector<std::vector<std::string>>>(1);
			return output;
		}

		std::shared_ptr<std::vector<std::vector<std::string>>> result = std::make_shared<std::vector<std::vector<std::string>>>();
		for (int i = 0; i < words.size(); i++)
		{
			if (target.find(words[i]) == 0)
			{
				std::string suffix = target.substr(words[i].size());
				std::shared_ptr<std::vector<std::vector<std::string>>> waysToConstruct = allCounstruct(words, suffix, mem);
				int size = waysToConstruct->size();
				if (size != 0)
				{
					for (int j = 0; j < size; j++)
					{
						(*waysToConstruct)[j].push_back(words[i]);
						std::swap((*waysToConstruct)[j][(*waysToConstruct)[j].size() - 1], (*waysToConstruct)[j][0]);
						result->push_back((*waysToConstruct)[j]);
					}
				}		
			}
		}
		(*mem)[target] = result;
		return result;
	}

	unsigned long long fib(int n)
	{
		std::vector<unsigned long long > table(n + 1);
		table[1] = 1;
		for (int i = 0; i < n; i++)
		{
			table[i + 1] += table[i];
			if (i != n - 1)
				table[i + 2] += table[i];
		}
		return table[n];
	}

	unsigned long long gridTraveler(int columns, int rows)
	{
		std::vector<std::vector<unsigned long long>> table(rows + 1);
		for (int i = 0; i <= rows; i++)
			table[i].resize(columns + 1);

		table[1][1] = 1;

		for (int i = 0; i <= rows; i++)
		{
			for (int j = 0; j <= columns; j++)
			{
				int current = table[i][j];
				if(j + 1 <= columns) 
					table[i][j + 1] += current;
				if (i + 1 <= rows)
					table[i + 1][j] += current;
			}
		}

		return table[rows][columns];
	}

	bool canSumTab(int target, std::vector<int>& nums)
	{
		std::vector<bool> table(target+1, false);
		table[0] = true;
		for (int i = 0; i < target; i++)
		{
			if (table[i])
			{
				for (int num: nums)
				{
					int current = num + i;
					if (current <= target)
						table[current] = true;
				}
			}
		}

		return table[target];
	}

	std::shared_ptr<std::vector<int>> howSumTab(int target, std::vector<int>& nums)
	{
		std::vector<std::shared_ptr<std::vector<int>>> table(target + 1, nullptr);
		table[0] = std::make_shared<std::vector<int>>();
		for (int i = 0; i < target; i++)
		{
			if (table[i] != nullptr)
			{
				for (int num : nums)
				{
					int current = num + i;
					if (current <= target)
					{
						if (table[current] == nullptr)
							table[current] = std::make_shared<std::vector<int>>();
						*table[current] = *table[i];
						table[current]->push_back(num);
					}
				}
			}
			
		}

		return table[target];
	}

	std::shared_ptr<std::vector<int>> bestSumTab(int target, std::vector<int>& nums)
	{
		std::vector<std::shared_ptr<std::vector<int>>> table(target + 1, nullptr);
		table[0] = std::make_shared<std::vector<int>>();
		for (int i = 0; i < target; i++)
		{
			if (table[i] != nullptr)
			{
				for (int num : nums)
				{
					int current = num + i;
					if (current <= target)
					{
						if (table[current] == nullptr)
							table[current] = std::make_shared<std::vector<int>>();
						std::vector<int> currentArr = *table[i];
						currentArr.push_back(num);
						int size = table[current]->size();
						if (size == 0 || currentArr.size() < size)
							*table[current] = currentArr;
					}
				}
			}

		}

		return table[target];
	}

	bool canConstuctTab(std::vector<std::string>& words, std::string& target)
	{
		int targetSize = target.size();
		std::vector<bool> table(targetSize + 1, false);
		table[0] = true;
		for (int i = 0; i < targetSize; i++)
		{
			if (table[i])
			{
				for (int wNum = 0; wNum < words.size(); wNum++)
				{
					int current = i + words[wNum].size();
					if (target.substr(i, current-i) == words[wNum])
						table[current] = true;
				}
			}
		}
		return table[targetSize];
	}

	int countConstuctTab(std::vector<std::string>& words, std::string& target)
	{
		int targetSize = target.size();
		std::vector<int> table(targetSize + 1, 0);
		table[0] = 1;
		for (int i = 0; i < targetSize; i++)
		{
			if (table[i] != 0)
			{
				for (int wNum = 0; wNum < words.size(); wNum++)
				{
					int current = i + words[wNum].size();
					if (target.substr(i, current - i) == words[wNum])
						table[current]+= table[i];
				}
			}
		}
		return table[targetSize];
	}

	std::shared_ptr<std::vector<std::string*>> howConstruct(std::vector<std::string>& words, std::string& target)
	{
		int targetSize = target.size();
		std::vector<std::shared_ptr<std::vector<std::string*>>> table(targetSize + 1, nullptr);
		table[0] = std::make_shared<std::vector<std::string*>>();
		for (int i = 0; i < targetSize; i++)
		{
			if (table[i] != nullptr)
			{
				for (int wNum = 0; wNum < words.size(); wNum++)
				{
					int current = i + words[wNum].size();
					if (target.substr(i, current - i) == words[wNum])
					{
						if (table[current] == nullptr)
							table[current] = std::make_shared<std::vector<std::string*>>();
						*table[current] = *table[i];
						table[current]->push_back(&(words[wNum]));
					}
				}
			}
		}
		return table[targetSize];
	}

	std::shared_ptr<std::vector<std::vector<std::string*>>> allConstruct(std::vector<std::string>& words, std::string& target)
	{
		int targetSize = target.size();
		std::vector<std::shared_ptr<std::vector<std::vector<std::string*>>>> table(targetSize + 1);
		for (int i = 0; i <= targetSize; i++)
		{
			table[i] = std::make_shared<std::vector<std::vector<std::string*>>>();
		}
		table[0]->resize(1);
		for (int i = 0; i < targetSize; i++)
		{
			for (int wNum = 0; wNum < words.size(); wNum++)
			{
				int current = i + words[wNum].size();
				if (target.substr(i, current - i) == words[wNum])
				{
					std::vector<std::vector<std::string*>> newArr = *table[i];
					int newSize = newArr.size();
					for (int j = 0; j < newSize; j++)
					{
						newArr[j].push_back(&(words[wNum]));
						table[current]->push_back(newArr[j]);
					}

				}
			}
		}
		return table[targetSize];
	}
}

namespace utils
{
	void log(std::vector<int>* inp)
	{
		if (inp != nullptr)
			for (int i = 0; i < inp->size(); i++)
				std::cout << (*inp)[i] << ", ";
		else
			std::cout << "nullptr";
		std::cout << std::endl;
	}
	void log(std::shared_ptr<std::vector<int>> inp)
	{
		if (inp != nullptr)
			for (int i = 0; i < inp->size(); i++)
				std::cout << (*inp)[i] << ", ";
		else
			std::cout << "nullptr";
		std::cout << std::endl;
	}
	void log(std::shared_ptr<std::vector<std::string*>> inp)
	{
		if (inp != nullptr)
			for (int i = 0; i < inp->size(); i++)
				std::cout << (*(*inp)[i]) << ", ";
		else
			std::cout << "nullptr";
		std::cout << std::endl;
	}
	void log(std::shared_ptr<std::vector<std::vector<std::string>>> inp)
	{
		if (inp != nullptr)
		{
			for (int i = 0; i < inp->size(); i++)
			{
				int size = (*inp)[i].size() - 1;
				for (int j = 0; j < size; j++)
				{
					std::cout << (*inp)[i][j] << ", ";
				}
				std::cout << (*inp)[i][size];
				std::cout << std::endl;
			}
		}
		else
			std::cout << "nullptr";
		std::cout << std::endl;
	}
	void log(std::shared_ptr<std::vector<std::vector<std::string*>>> inp)
	{
		if (inp != nullptr)
		{
			for (int i = 0; i < inp->size(); i++)
			{
				int size = (*inp)[i].size() - 1;
				for (int j = 0; j < size; j++)
				{
					std::cout << (*(*inp)[i][j]) << ", ";
				}
				std::cout << (*(*inp)[i][size]);
				std::cout << std::endl;
			}
		}
		else
			std::cout << "nullptr" << std::endl;
		std::cout << std::endl;
	}
}

int main()
{
	std::vector<std::string> words = { "ab", "abc", "cd", "def", "abcd", "ef", "c"};
	std::string input_word = "abcdef";
	utils::log(algos::allConstruct(words, input_word));

	words = { "bo", "rd", "ate", "t", "ska", "sk", "boar" };
	input_word = "skateboard";
	utils::log(algos::allConstruct(words, input_word));

	words = { "a", "p", "ent", "enter", "ot", "o", "t" };
	input_word = "enterapotentpot";
	utils::log(algos::allConstruct(words, input_word));

	words = { "e", "ee", "eee", "eeee", "eeeee" };
	input_word = "eeeeeeeeeeeeeeeeeeeeee";
	utils::log(algos::allConstruct(words, input_word));

	words = { "purp", "p", "ur", "le", "purpl"};
	input_word = "purple";
	utils::log(algos::allConstruct(words, input_word));

	
	return 0;
}
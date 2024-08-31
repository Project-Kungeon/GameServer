#pragma once
class RandomUtil
{
public:
	template<typename T>
	static T GetRandom(T min, T max);
};

template<typename T>
inline T RandomUtil::GetRandom(T min, T max)
{
	//std::random_device randomDevice;
	std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

	if constexpr (std::is_integral_v<T>)
	{
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(generator);
	}
	else
	{
		std::uniform_real_distribution<T> distribution(min, max);
		return distribution(generator);
	}
}

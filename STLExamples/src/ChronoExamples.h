#pragma once



void Chrono_Test()
{
	std::printf("\n---------------------Chrono Examples------------------------------------\n\n");

	std::chrono::duration<int>							twentySecs(20);
	std::chrono::duration<double, std::ratio<60>>		halfAMinute(0.5);
	std::chrono::duration<double, std::ratio<1, 1000>>	oneMillisecond(1);

	std::cout << "20 secs: " << twentySecs.count() << '\n';
	std::cout << "30 secs (Half a minute) : " << halfAMinute.count() << '\n';

	/*Chrono library built in definitions*/
	std::chrono::seconds		tenSecs(10);
	std::chrono::minutes		oneMinute(1);
	std::chrono::milliseconds	fiveMillisecs(5);
	std::chrono::hours			oneDay(24);

	std::cout << "Five millisecs: " << fiveMillisecs.count() << '\n';

	auto newduration = tenSecs - oneMinute;

	std::cout << newduration.count() << '\n';
	std::cout << newduration.count() * (-5) << '\n';
	std::cout << (++newduration).count() << '\n';

	std::cout << newduration << '\n';

	std::chrono::seconds sec(55);
	std::chrono::minutes m1;

	m1 = std::chrono::duration_cast<std::chrono::minutes>(sec);


	std::printf("\n---------------------Chrono Examples------------------------------------\n\n");
}

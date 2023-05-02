#include <iostream>
#include "container.h"
#include "task_object.h"



int main() {
	Container<Task*> task_container;

	Operation_task* task_add_1 = new Operation_task(2, 3, "Add");
	Operation_task* task_multiply_1 = new Operation_task(2, 5, "Multiply");
	Count_object* count_object_task_1 = new Count_object(task_container);
	Count_task_with_result* count_task_with_result_task = new Count_task_with_result(task_container);
	Operation_task* task_divide_1 = new Operation_task(6, 3, "Divide");
	Operation_task* task_divide_2 = new Operation_task(9, 3, "Divide");
	Count_total* count_total_task = new Count_total();
	Operation_task* task_multiply_2 = new Operation_task(10, 5, "Multiply");
	Operation_task* task_add_2 = new Operation_task(6, 7, "Add");
	Operation_task* task_subtract_1 = new Operation_task(10, 20, "Subtract");
	Operation_task* task_subtract_2 = new Operation_task(100, 35, "Subtract");
	Count_object* count_object_task_2 = new Count_object(task_container);

	Container<Task*> add_task_container;

	add_task_container.push_back(new Add_task(task_add_1, task_container));
	add_task_container.push_back(new Add_task(task_multiply_1, task_container));
	add_task_container.push_back(new Add_task(count_object_task_1, task_container));
	add_task_container.push_back(new Add_task(count_task_with_result_task, task_container));
	add_task_container.push_back(new Add_task(task_divide_1, task_container));
	add_task_container.push_back(new Add_task(task_divide_2, task_container));
	add_task_container.push_back(new Add_task(count_total_task, task_container));
	add_task_container.push_back(new Add_task(task_multiply_2, task_container));
	add_task_container.push_back(new Add_task(task_add_2, task_container));
	add_task_container.push_back(new Add_task(task_subtract_1, task_container));
	add_task_container.push_back(new Add_task(task_subtract_2, task_container));
	add_task_container.push_back(new Add_task(count_object_task_2, task_container));

	int counter = Object::get_counter();
	std::cout << "Total number of objects in program is " + std::to_string(counter) << std::endl;

	for (auto it = add_task_container.begin(); it != add_task_container.end(); it++) {
		it.value()->execute();
		delete it.value();
	}

	std::cout << "The size of the container with tasks is " + std::to_string(task_container.get_size()) << std::endl << std::endl;

	Container<std::string> task_info_container;

	for (auto it = task_container.begin(); it != task_container.end(); it++) {
		it.value()->execute();
		task_info_container.push_back(it.value()->toString());
		delete it.value();
	}


	std::cout << "Info about executed tasks:" << std::endl;
	for (auto it = task_info_container.begin(); it != task_info_container.end(); it++) {
		std::cout << it.value() << std::endl;
	}

	counter = Object::get_counter();
	std::cout << std::endl << "Total number of objects in program is " + std::to_string(counter) << std::endl;

	return 0;
}
#pragma once
#include <iostream>
#include <string>
#include "Container.h"



/*
Создать абстрактный класс Object с методом:  std::string toString() const = 0;
Добавить в класс Object счётчик, чтобы в любой момент можно было узнать, 
сколько существует объектов (экземпляров-наследников класса Object).
Унаследовать от него два класса: Task для задач (задача имеет возможность выполнить её)
и Named для именованных объектов.
*/

class Object {
private:
	static int counter;

public:

	Object() {
		counter++;
	}

	virtual ~Object() {
		counter--;
	}

	static int get_counter() {
		return counter;
	}

	virtual std::string const toString() const = 0;
};

int Object::counter = 0;



class Task : virtual public Object{
private:
	bool has_result = false;
	bool executed = false;

public:

	Task(bool has_result): has_result(has_result) {}

	virtual void execute() {
		executed = true;
	}

	bool is_executed() const {
		return executed;
	}

	bool does_have_result() const {
		return has_result;
	}
};



class Named: virtual public Object {
private:
	std::string name;

public:
	class InvalidTaskName {
	private:
		std::string info;
	public:
		InvalidTaskName(std::string string) : info(string) {}

		std::string get_info() const {
			return info;
		}
	};

	Named(std::string const & name): name(name) {}

	std::string get_name() const {
		return name;
	}
};



//Именованная задача с результатом для бинарных арифметических вычислений (+, -, *, /)
class Operation_task : public Task, public Named {
private:
	const double arg_1;
	const double arg_2;
	double result = 0;

public:
	Operation_task(double arg_1, double arg_2, std::string const & name): Task(true), Named(validate_name(name)),
		arg_1(arg_1), arg_2(arg_2) {}

	std::string validate_name(std::string const & name) const {
		if ((name == "Add") || (name == "Subtract") || (name == "Multiply") || (name == "Divide")) {
			return name;
		}
		else {
			throw InvalidTaskName("Invalid task name. Available names: Add, Subtract, Multiply, Divide.");
		}
	}

	void execute() override{
		Task::execute();
		std::string operation_name = get_name();
		if (operation_name == "Add") {
			result = arg_1 + arg_2;
		}
		else if (operation_name == "Subtract") {
			result = arg_1 - arg_2;
		}
		else if (operation_name == "Multiply") {
			result = arg_1 * arg_2;
		}
		else if (operation_name == "Divide") {
			result = arg_1 / arg_2;
		}
	}

	std::string const toString() const {
		std::string result_string;
		if (is_executed()) {
			result_string = get_name() + std::string(" task, argument_1 = ") + std::to_string(arg_1) + std::string(", argument_2 = ") + 
				std::to_string(arg_2) + std::string(". Result is ") + std::to_string(this->result);
		}
		else {
			result_string = get_name() + std::string(" task, argument_1 = ") + std::to_string(arg_1) + 
				std::string(", argument_2 = ") + std::to_string(arg_2);
		}
		return result_string;
	}
};



//Задача без результата для добавления другой указанной задачи в указанный список задач.
class Add_task: public Task {
private:
	Container<Task*>& container;
	Task* task;

public:
	Add_task(Task* task, Container<Task*>& container): Task(false), task(task), container(container) {}

	void execute() override{
		Task::execute();
		container.push_back(task);
	}

	std::string const toString() const {
		std::string result_string;
		if (is_executed()) {
			result_string = std::string("Adding task. Task was added to container");
		}
		else {
			result_string = std::string("Adding task");
		}
		return result_string;
	}
};



//Задача с результатом для вычисления количества Object в указанном списке объектов.
class Count_object : public Task {
private:
	Container<Task*> const& container;
	int result = 0;

public:
	Count_object(Container<Task*> const& container): Task(true), container(container) {}

	void execute() override {
		Task::execute();
		result = container.get_size();
	}

	std::string const toString() const {
		std::string result_string;
		if (is_executed()) {
			result_string = std::string("Task to count objects in container. Container contains ") +
				std::to_string(result) + std::string(" objects");
		}
		else {
			result_string = std::string("Task to count objects in container.");
		}
		return result_string;
	}
};



//Задача с результатом для вычисления количества задач с результатом в указанном списке задач.
class Count_task_with_result : public Task {
private:
	Container<Task*>& container;
	int result = 0;

public:
	Count_task_with_result(Container<Task*>& container) : Task(true), container(container) {}

	void execute() override {
		Task::execute();
		result = 0;
		for (auto it = container.begin(), end = container.end(); it != end; it++) {
			if (it.value()->does_have_result()) { result++; }
		}
	}

	std::string const toString() const {
		std::string result_string;
		if (is_executed()) {
			result_string = std::string("Task to count tasks with result in container. Container contains ") +
				std::to_string(result) + std::string(" tasks with result");
		}
		else {
			result_string = std::string("Task to count tasks with result in container.");
		}
		return result_string;
	}
};



//Безымянная задача без результата для очистки указанного списка объектов.
class Clear_task : public Task {
private:
	Container<Task*>& container;

public:
	Clear_task(Container<Task*>& container): Task(false), container(container) {}

	void execute() override {
		Task::execute();
		container.clear();
	}

	std::string const toString() const {
		std::string result_string;
		if (is_executed()) {
			result_string = std::string("Clearing task. Container was cleared ");
		}
		else {
			result_string = std::string("Clearing task.");
		}
		return result_string;
	}
};



//Задача с результатом, которая позволяет узнать, сколько всего существует Object в данный момент.
class Count_total : public Task {
private:
	int result = 0;

public:
	Count_total(): Task(true) {}

	void execute() override {
		Task::execute();
		result = Object::get_counter();
	}

	std::string const toString() const {
		std::string result_string;
		if (is_executed()) {
			result_string = std::string("Task to count total number of objects in program. Currently there are ") +
				std::to_string(result) + std::string(" objects in program");
		}
		else {
			result_string = std::string("Task to count total number of objects in program.");
		}
		return result_string;
	}
};
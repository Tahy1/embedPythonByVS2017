// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//http://blog.csdn.net/taiyang1987912/article/details/44779719
//http://blog.csdn.net/nynyvkhhiiii/article/details/17525865
//http://blog.csdn.net/fuyuehua22/article/details/42149703
//http://blog.csdn.net/shadow_dreamer/article/details/47817937 从C中向Python传入参数
#include "stdafx.h"
#include "Python.h"

//#pragma comment(lib, "python27_d.lib")
int main(int argc, char** argv)
{
	Py_Initialize();// 初始化python虚拟机  
	if (!Py_IsInitialized()) {
		return -1;
	}
	PyObject *pModule, *pFunc,*pRet, *list_item;
	/*另一种方式
		pName = PyString_FromString("clobrw");
		pModule = PyImport_Import(pName);//  加载clobrw.py文件
	*/
	pModule = PyImport_ImportModule("clobrw"); //  加载clobrw.py文件
	if (!pModule) {
		printf("can't find clobrw.py");
		getchar();
		return -1;
	}
	pFunc = PyObject_GetAttrString(pModule, "readDataFromOracle");
	pRet = PyObject_CallObject(pFunc, NULL);//获取返回值
	list_item = NULL;//python类型的列表元素
	int int_item;//C类型的列表元素
	PyObject *number, *angle, *velocity, *step;
	PyObject *time, *torque;
	number = NULL;
	time = NULL;
	angle = NULL;
	torque = NULL;
	velocity = NULL;
	step = NULL;
	PyArg_ParseTuple(pRet, "O|O|O|O|O|O", &number, &time, &angle, &torque, &velocity, &step);//从tuple中取出所有list
	int number_len = PyObject_Size(number);//返回列表长度
	int time_len = PyObject_Size(time);
	int angle_len = PyObject_Size(angle);
	int torque_len = PyObject_Size(torque);
	int velocity_len = PyObject_Size(velocity);
	int step_len = PyObject_Size(step);
	for (int i = 0; i < number_len; i++) {
		list_item = PyList_GetItem(number, i);//PyList_GetItem取回的值是str类型
		int_item = PyInt_AsLong(list_item); //转换成Long类型
		printf("%d\n", int_item);
	}
	double torque_item;
	for (int i = 0; i < number_len; i++) {
		list_item = PyList_GetItem(torque, i);//PyList_GetItem取回的值是str类型
		torque_item = PyFloat_AsDouble(list_item); //转换成Double类型
		printf("%f\n", torque_item);
	}
	Py_Finalize();
    return 0;
}


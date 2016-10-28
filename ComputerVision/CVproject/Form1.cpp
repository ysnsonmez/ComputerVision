#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CVproject::Form1 Form;
	Application::Run(%Form);

}
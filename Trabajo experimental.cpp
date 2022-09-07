#include <iostream>
#define A 2000 //Constante global para generar los numeros de cuenta
#define B 1000 //Constante global para generar los codigos de transaccion
using namespace std;
//La clave de acceso es 6942
//Armando estructuras
float transbank=0.5, pagserv=0.45; //valores globales (Costos de transaccion)(transbank [transferencias entre bancos distintos]; pagserv [pago de servicios])
int  numclient=0, numaccount=0, numtrans=0, movnum=0; //variables globales para los arreglos
//Estructura fecha para mayor comodidad
struct fecha{
	int dia, mes, anyo;
};

//Estructura cliente (client_id "numero de cedula o RUC"; client_name, client_lastname "Nombres y apellidos", client_email "correo electronico", client_address "Direccion", client_numcel "telefono/celular"
struct cliente {
	int client_code; //codigo del cliente
	char client_id[13], client_name[60], client_lastname[60], client_email[100], client_address[100], client_numcel[20];
	struct fecha fecnac; //fecha de nacimiento
	struct fecha fecing; //fecha de ingreso
	bool sexo; //sexo indicanto que Verdadero = Masculino; Falso = Femenino
	int state; //estado de la cuenta 1=activo; 2=inactivo; 3=eliminado
};

struct account {
	int client_code; //Codigo del cliente al que le pertenece la cuenta
	int num_account; //Numero de cuenta
	bool account_type; //account_type(tipo de cuenta) indicando que Verdadero = Ahorro; Falso = Corriente
	int cupo_retiro, cupo_trans, saldo; //cupo_retiro "cupo de retiro"; cupo_trans "cupo de transferencia"; saldo "saldo del cliente"
	struct fecha fecing; //fecha de ingreso
	int state; //estado de la cuenta
};

struct movimientos {
	int trans_code; //codigo de transaccion
	bool trans_type; //trans_type es booleano indicando que Verdadero = Credito; Falso = Debito
	int account_num1, account_num2; //numero de cuenta 1 es del que sale el dinero y el 2 el que lo recibe
	float cost;
	struct fecha fectrans; //fecha de transaccion
	int state; //estado de la cuenta
};

struct transtype {
	int trans_code; //codigo de transaccion
	char trans_description[300]; //descripcion de la transaccion
	float cost; //costo de transaccion
	int state; //estado de la cuenta
};

bool inicio()
{
	int clave, trys=0; //clave "la clave a ingresar (6942)"; trys "numeros de intentos"
	do{
		system("cls");
		cout<<"******BIENVENIDO******\n\n";
		cout<<"Ingrese la clave de acceso....: ";
		cin>>clave;
		
		if(clave==6942)							//Comprobacion si la clave esta correcta
		{
			cout<<"\n\nAcceso concedido...\n";
			system("pause");
			return true;
		}else
		{
			cout<<"\n\nClave incorrecta!\n";
			trys++;
			if(trys!=3)
			{
				cout<<"Vuelva a intentarlo...\n\n";
			}
			system("pause");
		}
	}while(trys<3); //en caso de que tenga 3 intentos fallidos cerrar el programa
	system("cls");
	cout<<"\n\nACCESO DENEGADO!!\nCLABE BLOQUEADA, LLAME AL DEPARTAMENTO DE SISTEMAS.";
	return false;
}

void ingresocliente(struct cliente client_data[500]) //recibe en estructura cliente client_data[500]
{
	int sex; //variable sex para la identificacion del genero del cliente
		system("cls");
				cout<<"Ingrese los datos del cliente:\n";
				client_data[numclient].client_code=numclient+1;	fflush(stdin);
				cout<<"\nCliente "<<client_data[numclient].client_code;
				cout<<"\nIngrese la Cedula/RUC del cliente: ";
				gets(client_data[numclient].client_id);	fflush(stdin);
				cout<<"\nIngrese los apellidos del cliente: ";										//Pedida de datos del cliente
				gets(client_data[numclient].client_lastname);	fflush(stdin);
				cout<<"\nIngrese los nombres del cliente: ";
				gets(client_data[numclient].client_name);	fflush(stdin);
				cout<<"\nIngrese la fecha de nacimiento del cliente: ";				cout<<"\nDia: ";
																					cin>>client_data[numclient].fecnac.dia;	fflush(stdin);
																					cout<<"\nMes: ";
																					cin>>client_data[numclient].fecnac.mes;	fflush(stdin);
																					cout<<"\nAnyo: ";
																					cin>>client_data[numclient].fecnac.anyo;	fflush(stdin);
				cout<<"\n1. Masculino";
				cout<<"\n2. Femenino\n";
				cout<<"Ingrese el genero: ";
				cin>>sex;	fflush(stdin);
				if(sex<1 || sex>2)			//comprobacion del genero del cliente
				{
					cout<<"\nIngrese una opcion valida: ";
				}else
				{
					if(sex==1)			//Verdadero = Masculino; Falso = Femenino
					{
						client_data[numclient].sexo=true; 
					}else
					{
						client_data[numclient].sexo=false;
					}
				}
				cout<<"\nIngrese el correo electronico: ";
				gets(client_data[numclient].client_email);	fflush(stdin);
				cout<<"\nIngrese el numero de telefono: ";
				gets(client_data[numclient].client_numcel);	fflush(stdin);
				cout<<"\nIngrese Direccion: ";
				gets(client_data[numclient].client_address); fflush(stdin);
				cout<<"\nIngrese la fecha de ingreso: ";							cout<<"\nDia: ";
																					cin>>client_data[numclient].fecing.dia;	fflush(stdin);
																					cout<<"\nMes: ";
																					cin>>client_data[numclient].fecing.mes;	fflush(stdin);
																					cout<<"\nAnyo: ";
																					cin>>client_data[numclient].fecing.anyo;	fflush(stdin);
				cout<<"\n1. Activo";
				cout<<"\n2. Inactivo";
				cout<<"\n3. Eliminado";
				cout<<"\nIngrese el estado de la cuenta: ";
				cin>>client_data[numclient].state;	fflush(stdin);
				numclient++;
				cout<<"\n\nINGRESO DE DATOS EXITOSO!!!\n\n";
				system("pause");
}

void ingresocuenta(struct account account_data[500])
{
	int accounttype; //Variable para determinar el tipo de cuenta
	system("cls");
					cout<<"******CUENTAS******\n";
					cout<<"Ingrese el numero del cliente: ";
					cin>>account_data[numaccount].client_code;  //Ingreso del codigo del cliente al que le pertenece la cuenta
					if(numaccount==0)
					{
						account_data[numaccount].num_account=A;
					}else
					{
						account_data[numaccount].num_account=account_data[numaccount-1].num_account+1; //Asignacion del numero de cuenta en caso de que sea la primera es el valor de A (2000) caso contrario sumar 1 al valor de la cuenta anterior
					}
					cout<<"\nNumero de cuenta: "<<account_data[numaccount].num_account;
					cout<<"\n1. Ahorro\n";
					cout<<"\n2. Corriente\n";
					cout<<"\nSeleccione el tipo de cuenta: ";
					cin>>accounttype;
					if(accounttype<1 || accounttype>2) 				//Verdadero = Ahorros; Falso= Corriente
					{
						cout<<"\nIngrese una opcion valida:\n";
					}else
					{
						if(accounttype==1)
						{
							account_data[numaccount].account_type=true;
						}else
						{
							account_data[numaccount].account_type=false;
						}
					}
					
					cout<<"\nIngrese el cupo de retiro: ";
					cin>>account_data[numaccount].cupo_retiro;
					cout<<"\nIngrese el cupo de transferencia: ";
					cin>>account_data[numaccount].cupo_trans;
					cout<<"\nIngrese el saldo inicial: ";
					cin>>account_data[numaccount].saldo;
					cout<<"\nFecha de Ingreso: ";					cout<<"\nInrgrese el dia: ";
																	cin>>account_data[numaccount].fecing.dia;		//pedida de datos de la cuenta
																	cout<<"\nIngrese el mes: ";
																	cin>>account_data[numaccount].fecing.mes;
																	cout<<"\nIngrese el anyo: ";
																	cin>>account_data[numaccount].fecing.anyo;
					cout<<"\n\t1. Activo";
					cout<<"\n\t2. Inactivo";
					cout<<"\n\t3. Eliminado";
					cout<<"\nIngrese el estado de la cuenta: ";
					cin>>account_data[numaccount].state;		fflush(stdin);
					
					if(account_data[numaccount].state<1 || account_data[numaccount].state>3)
					{
						cout<<"\nIngrese una opcion valida...";
					}
					
					cout<<"\n\nINGRESO DE CUENTA EXITOSO\n\n";
					numaccount++;
					system("pause");
}

void ingresotransacciones(struct cliente client_data[500], struct account account_data[500], struct transtype trans_data[1000], struct movimientos mov_data[1000])
{
	system("cls");
	int numtrans_1, i;
	cout<<"******INGRESO TRANSACCIONES******";
	cout<<"\n\nIngrese el numero de transaccion: ";
	cin>>numtrans_1;
	for(i=0;i<movnum;i++)
	{
		if(numtrans_1==mov_data[i].trans_code)
		{
			if(mov_data[i].trans_type)
			{
				cout<<"\nTipo de transaccion: Debito";
			}else
			{
				cout<<"\nTipo de transaccion: Credito";
			}
			cout<<"\nFecha de la transsaccion: "<<mov_data[i].fectrans.dia<<"/"<<mov_data[i].fectrans.mes<<"/"<<mov_data[i].fectrans.anyo;
			switch(mov_data[i].state)
			{
				case 1: cout<<"\nEstado de la transaccion: Activo"; break;
				case 2: cout<<"\nEstado de la transaccion: Inactivo"; break;
				case 3: cout<<"\nEstado de la transaccion: Eliminado"; break;
			}
			cout<<"\nNumero de cuenta depositante: "<<mov_data[i].account_num1;
			cout<<"\nNumero de cuenta receptor: "<<mov_data[i].account_num2;
			cout<<"\nCosto de la transaccion: "<<mov_data[i].cost;
			trans_data[numtrans].trans_code=mov_data[i].trans_code;
			trans_data[numtrans].state=mov_data[i].state;
			cout<<"\nIngrese la descripcion de la transaccion";		fflush(stdin);
			gets(trans_data[numtrans].trans_description);
			numtrans++;
			system("pause");
		}else
		{
			cout<<"\nNumero de transaccion inexitente...";
		}
	}
	
	
	
	
	
}

void ingreso(struct cliente client_data[500], struct account account_data[500], struct transtype trans_data[1000], struct movimientos mov_data[1000]) //recibe arreglos
{
	int opc;	//variable opc para controlar el menu
	do
	{
		system("cls");
		cout<<"******INRGESO******\n\n";
		cout<<"1. Clientes\n";
		cout<<"2. Cuentas\n";
		cout<<"3. Transacciones\n";
		cout<<"4. Regresar al menu anterior\n\n";
		cout<<"Ingrese una opcion: ";
		cin>>opc; fflush(stdin);
		switch(opc)
		{
			case 1: ingresocliente(client_data); break;
				
			case 2: ingresocuenta(account_data); break;
					
			case 3: ingresotransacciones(client_data, account_data, trans_data, mov_data); break;
					
			case 4: break;
			
			default: cout<<"\nIngrese una opcion valida...";	break;
		}
	
	}while(opc!=4);
	
}

void consultageneralclientes(struct cliente client_data[500]) //funcion para la consulta general
{
	int i; //variable i para controlar el for
	system("cls");
	fflush(stdin);
	cout<<"\nCodigo\tCEDULA/RUC\tNombres\t\tApellidos\tGenero\tCorreo electronico\tDireccion\tTelefono    Nacimiento\tIngreso\tEstado de cuenta\n";
	for(i=0;i<numclient;i++) //ciclo for para mostrar todos los arreglos
	{
		cout<<"\n"<<client_data[i].client_code<<"\t";
		cout<<client_data[i].client_id<<"\t";
		cout<<client_data[i].client_name<<"\t";
		cout<<client_data[i].client_lastname<<"\t";
		if(client_data[i].sexo)
		{
			cout<<"Masculino\t";							//muestra de datos de todos los clientes
		}else
		{
			cout<<"Femenino\t";
		}
		cout<<client_data[i].client_email<<"\t";
		cout<<client_data[i].client_address<<"\t";
		cout<<client_data[i].client_numcel<<"\t";
		cout<<client_data[i].fecnac.dia<<"/"<<client_data[i].fecnac.mes<<"/"<<client_data[i].fecnac.anyo<<"\t";
		cout<<client_data[i].fecing.dia<<"/"<<client_data[i].fecing.mes<<"/"<<client_data[i].fecing.anyo<<"\t";
		switch(client_data[i].state)
		{
			case 1: cout<<"Activa"; break;
			case 2: cout<<"Inactiva"; break;
			case 3: cout<<"Elimiinada"; break;
		}
	}
	cout<<endl<<endl;
	system("pause");
}

void consultacodigoclientes(struct cliente client_data[500])
{
	int search_clientcode, i; //variable search_clientcode para buscar el cliente (variable ingresada por el usuario); variable i para controlar el ciclo for
	system("cls");
	do{
		cout<<"Ingrese 0 para regresar al menu anterior."; //control para de que en caso no halla ningun cliente y se halla ingresado de forma accidental a esta opcion
		cout<<"\nIngrese el codigo del cliente: ";
		cin>>search_clientcode;		fflush(stdin);
		if(search_clientcode==0)
		{
			break; //en caso de ingresar 0 acaba la funcion
		}
		if(search_clientcode<0 || search_clientcode>numclient)
		{
			cout<<"CODIGO INEXISTENTE!";  //control para codigos inexistentes
			system("pause");
		}
	}while(search_clientcode<=0 || search_clientcode>numclient);
	
	for(i=0;i<numclient;i++)  //busqueda del cliente por el codigo
	{
		if(client_data[i].client_code==search_clientcode)
		{
			cout<<"\n\nCodigo: "<<client_data[i].client_code;
			cout<<"\nCDU/RUC: "<<client_data[i].client_id;
			cout<<"\nApellidos: "<<client_data[i].client_lastname;
			cout<<"\nNombres: "<<client_data[i].client_name;
			if(client_data[i].sexo)
			{
				cout<<"\nGenero: Masculino";
			}else
			{
				cout<<"\nGenero: Femenino";
			}
			cout<<"\nCorreo Electronico: "<<client_data[i].client_email;
			cout<<"\nDireccion: "<<client_data[i].client_address;
			cout<<"\nTelefono/Celular: "<<client_data[i].client_numcel;
			cout<<"\nFecha de nacimiento: "<<client_data[i].fecnac.dia<<"/"<<client_data[i].fecnac.mes<<"/"<<client_data[i].fecnac.anyo;
			cout<<"\nFecha de ingreso: "<<client_data[i].fecing.dia<<"/"<<client_data[i].fecing.mes<<"/"<<client_data[i].fecing.anyo;
			switch(client_data[i].state)
			{
				case 1: cout<<"\nEstado: Activa\n"; break;
				case 2: cout<<"\nEstado: Inactiva\n"; break;
				case 3: cout<<"\nEstado: Elimiinada\n"; break;
			}
			
		}
	}
	system("pause");
}

void consultageneralcuentas(struct account account_data[500])
{
	int i;
	system("cls");
	cout<<"Cliente\tNumCuenta\tTipo de cuenta\tCupo retiro\tCupo transferencia\tSaldo\tFecha de ingreso\tEstado\n";
	for(i=0;i<numaccount;i++)
	{
		cout<<endl<<account_data[i].client_code<<"\t";
		cout<<account_data[i].num_account<<"\t\t";
		if(account_data[i].account_type)
		{
			cout<<"Ahorros\t\t";
		}else
		{
			cout<<"Corriente\t\t";
		}
		cout<<account_data[i].cupo_retiro<<"\t\t";
		cout<<account_data[i].cupo_trans<<"\t\t\t";
		cout<<account_data[i].saldo<<"\t\t";
		cout<<account_data[i].fecing.dia<<"/"<<account_data[i].fecing.mes<<"/"<<account_data[i].fecing.anyo<<"\t";
		switch(account_data[i].state)
		{
			case 1: cout<<"Activa\n"; break;
			case 2: cout<<"Inactiva\n"; break;
			case 3: cout<<"Elimiinada\n"; break;
		}		
	}
	system("pause");
}

void consultacodigocuenta(struct account account_data[500])
{
		system("cls");
		int search_account, i; //Variable search_account ingresada por el usuario para poder buscar el numero de cuenta
		do{
			cout<<"Ingrese 0 para regresar al menu anterior."; //control para de que en caso no halla ningun numero de cuenta y se halla ingresado de forma accidental a esta opcion
			cout<<"\nIngrese el numero de cuenta: ";
			cin>>search_account;
				if(search_account==0)
			{
				break; //en caso de ingresar 0 acaba la funcion
			}
			if(search_account<0 || search_account>account_data[numaccount-1].num_account)
			{
				cout<<"NUMERO INEXISTENTE!";  //control para numeros inexistentes
				system("pause");
			}
		}while(search_account<0 || search_account>account_data[numaccount-1].num_account);
		
		for(i=0;i<numaccount;i++)  //busqueda del cliente por el codigo
		{
				if(account_data[i].num_account==search_account)
				{
					cout<<"\nCodigo de cliente: "<<account_data[i].client_code;
					if(account_data[i].account_type)
					{
						cout<<"\nCuenta: Ahorros";
					}else
					{
						cout<<"\nCuenta: Corriente";
					}
					cout<<"\nCupo de retiro: "<<account_data[i].cupo_retiro;
					cout<<"\nCupo de transferencia: "<<account_data[i].cupo_trans;
					cout<<"\nSaldo: "<<account_data[i].saldo;
					cout<<"\nFecha de ingreso: "<<account_data[i].fecing.dia<<"/"<<account_data[i].fecing.mes<<"/"<<account_data[i].fecing.anyo<<"\t";
					switch(account_data[i].state)
					{
						case 1: cout<<"\nEstado: Activa\n"; break;
						case 2: cout<<"\nEstadp: Inactiva\n"; break;
						case 3: cout<<"\nEstado: Elimiinada\n"; break;
					}		
					
				}
		}
	system("pause");
}

void consultas(struct cliente client_data[500], struct account account_data[500], struct movimientos mov_data[1000], struct transtype trans_data[1000])
{
	int opc, opc_1, opc_2; //varias variables opc para controlar las funciones switch
	system("cls");
	cout<<"******CONSULTAS******";
	cout<<"\n1. Clientes";
	cout<<"\n2. Cuentas";
	cout<<"\n3. Movimientos";
	cout<<"\n4. Regresar al menu anterior";
	cout<<"\n\nIngrese una opcion: ";
	cin>>opc; fflush(stdin);
	switch(opc)	
	{
		case 1:
			do
			{
			system("cls");
			cout<<"******CONSULTAS CLIENTES******";
			cout<<"\n1. Consulta general";
			cout<<"\n2. Consulta por codigo de cliente";
			cout<<"\n3. Regresar al menu anterior";
			cout<<"\nIngrese una opcion: ";
			cin>>opc_1; fflush(stdin);
			
			switch(opc_1)
			{
				case 1: consultageneralclientes(client_data); break;
				case 2: consultacodigoclientes(client_data); break;
				case 3: break;
				default: cout<<"Ingrese una opcion valida..."; break;
			}
			
			
			}while(opc_1!=3); break;
		
		case 2: do
				{
					system("cls");
					cout<<"******CONSULTA CUENTAS******";
					cout<<"\n1. Consulta general";
					cout<<"\n2. Consulta por numero de cuenta";
					cout<<"\n3. Regresar al menu anterior";
					cout<<"\nIngrese una opcion: ";
					cin>>opc_2;
					switch(opc_2)
					{
						case 1: consultageneralcuentas(account_data); break;
						case 2: consultacodigocuenta(account_data); break; 
					}
								
			
				}while(opc_2!=3);
	
	
	}
}

void depositos(struct movimientos mov_data[1000], struct cliente client_data[500], struct transtype trans_data[1000], struct account account_data[500])
{
	system("cls");
	int numaccount_1, i, j, k, l, dep, numaccount_2;
	cout<<"******DEPOSITOS******";
		cout<<"\nIngrese el numero de cuenta: ";
		cin>>numaccount_1;
		for(i=0;i<numaccount;i++)
		{
			if(numaccount_1==account_data[i].num_account)
			{
			for(j=0; j<numclient; j++)
				{
					if(account_data[i].client_code==client_data[j].client_code)
					{
						if(account_data[i].state==1 && client_data[j].state==1)
						{
								numtrans++;
								cout<<"\nNumero de transaccion: "<<numtrans;
								cout<<"\nCodigo: "<<account_data[i].client_code;
								cout<<"\nNombres: "<<client_data[j].client_name<<" "<<client_data[j].client_lastname;
								cout<<"\nCDU/RUC: "<<client_data[j].client_id;
								cout<<"\nIngrese al numero de cuenta al cual va a depositar: ";
								cin>>numaccount_2;
								for(k=0; k<numaccount; k++)
								{
									if(numaccount_2==account_data[k].num_account)
									{
											for(l=0; l<numclient; l++)
											{
												if(account_data[k].client_code==client_data[l].client_code)
												{
													if(account_data[k].state==1 && client_data[l].state==1)
													{
													cout<<"\nCodigo: "<<client_data[l].client_code;
													cout<<"\nNombres: "<<client_data[l].client_name<<" "<<client_data[l].client_lastname;
													cout<<"\nCDU/RUC: "<<client_data[l].client_id;
													cout<<"\n\nInrgese el valor a depositar: ";
													cin>>dep;
													if(dep>account_data[i].saldo)
													{
														cout<<"\nSaldo insuficiente";
													}else
													{
														account_data[i].saldo=account_data[i].saldo-dep;
														account_data[k].saldo=account_data[k].saldo+dep;
														cout<<"\nSaldo del depositante: "<<account_data[i].saldo;
														cout<<"\nSaldo del receptor: "<<account_data[k].saldo;
														cout<<"\n\nIngrese la fecha del deposito: ";
														cout<<"\nDia: ";
														cin>>mov_data[movnum].fectrans.dia;
														cout<<"\nMes: ";
														cin>>mov_data[movnum].fectrans.mes;
														cout<<"\nAnyo: ";
														cin>>mov_data[movnum].fectrans.anyo;
														mov_data[movnum].cost=dep;
														mov_data[movnum].trans_code=movnum+1;
														mov_data[movnum].state=1;
														mov_data[movnum].account_num1=numaccount_1;
														mov_data[movnum].account_num2=numaccount_2;
														mov_data[movnum].trans_type=true;
														movnum++;
														system("pause");
													}
													}else
														{
															if(account_data[k].state==2)
															{
																cout<<"\nEstado de la cuenta Inactiva...";
															}else
															{
																if(account_data[k].saldo==3)
																{
																	cout<<"\nEstado de la cuenta Eliminada";
																}else
																{
																	if(client_data[l].state==2)
																	{
																		cout<<"\nEstado del cliente Inactivo";
																	}else
																	{
																		cout<<"\nEstado del cliente eliminado";
																	}
																}
															}
														}
													}
												}
									}else
									{
										cout<<"\nNumero de cuenta inexistente...";
									}
								}
								
						}else
						{
							if(account_data[i].state==2)
							{
								cout<<"\nEstado de la cuenta Inactiva";  system("pause"); break;
							}else
							{
								if(account_data[i].state==3)
								{
									cout<<"\nEstado de la cuenta Eliminada"; system("pause"); break;
								}else
								{
									if(client_data[j].state==2)
									{
										cout<<"\nEstado del cliente Inactivo"; system("pause"); break;
									}else 
									{
										cout<<"\nEstado del cliente Eliminado"; system("pause"); break;
									}
								}
							}
						}
					}
				}
			}
			cout<<"Numero de cuenta inexistente...";
	}
}

void procesos(struct cliente client_data[500], struct account account_data[500], struct movimientos mov_data[1000], struct transtype trans_data[1000])
{
	int opc;
	system("cls");
	cout<<"******Procesos******";
	cout<<"\n1. Depositos";
	cout<<"\n2. Retiro";
	cout<<"\n3. Transferencia entre cuenta propia";
	cout<<"\n4. Transferencia a cuenta de terceros";
	cout<<"\n5. Transferencia a otros bancos";
	cout<<"\n6. Regresar al menu anterior";
	cout<<"\nIngrese una opcion: ";
	cin>>opc;
	switch(opc)
	{
		case 1: depositos(mov_data, client_data, trans_data, account_data); break;
	}
	
}
void grabar(struct cliente client_data[500], struct transtype trans_data[1000], struct movimientos mov_data[1000], struct account account_data[500])
{
	int i;
	FILE* (fichero);
	system("cls");
	
	fichero = fopen("cuentas.txt", "w");
	
	if(fichero==NULL)
	{
		cout<<"\nError al guardar los datos";
	}else
	{
		for(i=0; i<numclient; i++)
		{
		cout<<"\nwriting";

			fwrite(&client_data[i],sizeof(struct cliente),1,fichero);
		}
		// for(i=0; i<numaccount; i++)
		// {
		// 	fwrite(&account_data[i],sizeof(struct account),1,fichero);
		// }
		// for(i=0; i<numtrans; i++)
		// {
		// 	fwrite(&trans_data[i],sizeof(struct transtype),1,fichero);
		// }
		// for(i=0; i,movnum; i++)
		// {
		// 	fwrite(&mov_data[i],sizeof(struct movimientos),1,fichero);
		// }
		fclose(fichero);
	}
	system("pause");
}

main()
{
	bool verificacion; //variable verificacion para verificar que la clave sea correcta
	struct cliente client_data[500];
	struct transtype trans_data[1000];
	struct movimientos mov_data[1000];
	struct account account_data[500]; //Estructuras para guardar datos
	int opc;
	FILE* (fichero);
	fichero = fopen("cuentas.txt", "r");
	
	if(fichero==NULL)
	{
		cout<<"\nError al cargar los datos...\n\n";
		system("pause");
	}else
	{
		while(fread(&client_data[numclient],sizeof(struct cliente),1,fichero))
	        numclient++;
        	
		// while(!feof(fichero))
	 //    {
	 //    // fread(&account_data[numaccount],sizeof(struct account),1,fichero);
		// fread(&client_data[numclient],sizeof(struct cliente),1,fichero);
		// // fread(&mov_data[movnum],sizeof(struct movimientos),1,fichero);
		// // fread(&trans_data[numtrans],sizeof(struct transtype),1,fichero);
	 //     if (!feof(fichero))
	 //        numaccount++;
	 //        // numclient++;
	 //        // movnum++;
	 //        // numtrans++;
	 //    }
	    fclose(fichero);
	}
	verificacion=inicio();
	if(verificacion)
	{
		system("cls");
		do
		{
			system("cls");
			cout<<"******BIENVENIDO USUARIO******\n\n";
			cout<<"1. Ingreso\n";
			cout<<"2. Procesos\n";
			cout<<"3. Consultas\n";
			cout<<"4. Grabar archivos\n";
			cout<<"5. Salir\n\n";
			cout<<"Ingrese una opcion: ";
			cin>>opc;
			switch(opc)
			{
				case 1: ingreso(client_data, account_data, trans_data, mov_data); break;
				case 2: procesos(client_data, account_data, mov_data, trans_data); break;
				case 3: consultas(client_data, account_data, mov_data, trans_data); break;
				case 4: grabar(client_data, trans_data, mov_data, account_data); break;
				case 5: cout<<"\n\nSALIENDO..."; break;
				default: cout<<"OPCION INVALIDA, INTENTELO NUEVAMENTE....\n"; system("pause"); break;
			}
		}while(opc!=5);
	}
}

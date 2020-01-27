#include <thread>
#include <ctime>

#include "Functions.h"

void saveGame();

bool menuLoop = false;
int idUser;
int charIndex;

int aCharactersCount(std::array<Character, 5> _array)
{
	int count = 0;
	short int size = _array.size();
	for (size_t i = 0; i < size; i++) if (_array[i].level > 0) count++;
	return count;
}

void LoginMenu()
{
	system("cls");
	int a;
	std::cout << "1. Iniciar sesion\n2. Crear cuenta\n3. Salir\n";
	std::cin >> a;

	switch (a)
	{
	case 1:
		LoginUser();
		break;
	case 2:
		RegisterUser();
		break;
	case 3:
		gameLoop = false;
		break;
	default:
		break;
	}
}

void LoginUser()
{
	std::string userNameA;
	std::string userPswdA;

	bool aux = true;
	int userVectorSize = users.size();
	while (aux == true)
	{
		system("CLS");
		std::cout << "Indica a continuación su nombre de usuario y contraseña por favor." << std::endl;
		std::cout << "Nombre de usuario: ";
		std::cin >> userNameA;
		std::cout << "Contraseña: ";
		std::cin >> userPswdA;
		std::cout << std::endl;

		for (int i = 0; i < userVectorSize; i++)
		{
			if (userNameA == users[i].name && userPswdA == users[i].password )
			{
				std::cout << "¡Bienvenido, " << users[i].name << "!" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				idUser = i;
				menuLoop = true;
				return;
			}
		}
		aux = false;
		std::cout << "\nEl usuario y/o la contraseña introducidos no coinciden.\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

void RegisterUser()
{
	std::string userName, psswrd;
	std::cout << "Introduce tu nombre de usuario: ";
	std::cin >> userName;
	std::cout << "Introduce tu contraseña: ";
	std::cin >> psswrd;
	User AuxUser(userName, psswrd);
	users.push_back(AuxUser);
	idUser = users.size()-1;
	menuLoop = true;
}

void PlayerMenu(int& _countaUsers)
{
	int R;
	system("CLS");
	std::cout << "Menu del jugador: " << users[idUser].name << "\n\n\n";
	std::cout << "1. Jugar.\n";
	std::cout << "2. Crear personaje.\n";
	std::cout << "3. Listar personajes.\n";
	std::cout << "4. Eliminar personaje.\n";
	std::cout << "5. Eliminar cuenta.\n";
	std::cout << "6. Cerrar sesión.\n";
	std::cout << "7. Salir\n\n";
	std::cin >> R;
	if (R > 0 && R <= 7)
	{
		switch (R)
		{
		case 1:
			Play();
			break;
		case 2:
			NewCharacter();
			break;
		case 3:
			ListCharcatersUser();
			break;
		case 4:
			DeleteCharacterUser();
			break;
		case 5:
			DeleteUserUser();
			break;
		case 6:
			saveGame();
			idUser = NULL;
			menuLoop = false;
			break;
		case 7:
			saveGame();
			idUser = NULL;
			menuLoop = false;
			gameLoop = false;
			break;
		default:
			break;
		}
	}
	else
	{
		std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
		std::cin.get();
	}
	std::cin.ignore();
}

void AdminMenu(int& _countaUsers)
{
	int R;
	system("CLS");
	std::cout << "Menu del administrador: " << users[idUser].name << "\n\n\n";
	std::cout << "1. Listar cuentas de jugador.\n";
	std::cout << "2. Eliminar cuenta de jugador.\n";
	std::cout << "3. Mostrar personajes de un jugador.\n";
	std::cout << "4. Eliminar personaje de jugador.\n";
	std::cout << "5. Cerrar sesión.\n";
	std::cout << "6. Salir.\n\n";
	std::cin >> R;
	if (R > 0 && R <= 6)
	{
		switch (R)
		{
		case 1:
			ListUsers();
			break;
		case 2:
			DeleteUserAdmin();
			break;
		case 3:
			ListCharactersAdmin();
			break;
		case 4:
			DeleteCharacterAdmin();
			break;
		case 5:
			saveGame();
			menuLoop = false;
			break;
		case 6:
			saveGame();
			menuLoop = false;
			gameLoop = false;
			break;
		}
	}
	else
	{
		std::cout << "El  valor que has puesto no coincide con ninguna opción. Vuelve a intentarlo.";
		std::cin.get();
	}
	std::cin.ignore();
}

void Play()
{
	bool playLoop = true;
	while (playLoop)
	{
		int R;
		system("cls");
		int aCharCount = aCharactersCount(users[idUser].characters);
		std::cout << "Con que personaje deseas jugar?\n";
		size_t i;
		for (i = 0; i < aCharCount; i++)
		{
			std::cout << i + 1 << ". " << users[idUser].characters[i].name << std::endl;
		}
		std::cout << "\n" << i + 1 << ". Salir.\n\n";

		std::cin >> R;
		charIndex = R - 1;
		if (R == i + 1)
		{
			playLoop = false;
			return;
		}
		std::cout << "Has seleccionado este personaje: " << users[idUser].characters[charIndex].name;
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));

		system("cls");

		std::cout << "1. Cargar dungeon.\n";
		std::cout << "2. Generar proceduralmente.\n";
		std::cout << "3. Salir.\n\n";
		std::cin >> R;
		switch (R)
		{
		case 1:
			void loadGameState();
			loadGameState();
			break;
		case 2:
			playLoop = false;
			startGame();
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}
}

void DeleteUserUser()
{
	bool DeleteLoop = true;
	while (DeleteLoop == true)
	{
		char R;
		std::cout << "Estás seguro de que deseas eliminar esta cuenta? (S/N)";
		std::cin >> R;
		if (R == 's' || R == 'S')
		{
			users.erase(users.begin()+idUser);
			DeleteLoop = false;
			menuLoop = false;
		}
		else if (R == 'n' || R == 'N')
		{
			DeleteLoop = false;
		}
		else
		{
			std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			system("CLS");
		}
	}
}

void DeleteUserAdmin()
{
	bool DeleteLoop = true;
	while (DeleteLoop)
	{
		system("CLS");
		int R;
		std::cout << "Que cuenta deseas eliminar?\n\n";
		for (size_t i = 1; i < users.size(); i++)
		{
			std::cout << "\n" << i << ". Nombre de usario: " << users[i].name << "\n";
		}
		std::cout << "\n" << users.size() << ". Salir.\n";
		std::cin >> R;
		if (R > 0 && R < users.size() && users.size() != 1)
		{
			char RS;
			std::cout << "Estás seguro de que deseas eliminar el usuario \"" << users[R].name << "\"? (S/N)";
			std::cin >> RS;
			if (RS == 's' || RS == 'S')
			{
				users.erase(users.begin()+R);
			}
			else if (RS != 'n' || RS != 'N')
			{
				std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				system("CLS");
			}
		}
		else if (R == users.size())
		{
			system("CLS");
			DeleteLoop = false;
		}
		else
		{
			std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			system("CLS");
		}
	}
}

void NewCharacter()
{
	system("CLS");
	
	int aCharCount = aCharactersCount(users[idUser].characters);

	if (aCharCount == users[idUser].characters.size())
	{
		std::cout << "Has alcanzado el límite de personajes permitidos. Si quieres crear un nuevo personaje, elimina alguno desdel MENÚ DE OPCIONES DEL JUGADOR.\n\n";
		std::cout << "Pulsa Enter para regresar al MENU DE OPCIONES DEL JUGADOR.";
		std::cin.get();
	}
	else
	{
		Character character;
		int raceR;
		std::string nameR;
		bool canswerloop = true;
		while (canswerloop == true)
		{
			std::cout << "Elige una de las siguientes razas para tu personaje, introduciendo su número:\n";
			std::cout << "	1. Bárbaro.\n";
			std::cout << "	2. Asesino.\n";
			std::cout << "	3. Arquero.\n";
			std::cout << "	4. Nigromante.\n";
			std::cout << "	5. Hechicero.\n";
			std::cout << "	6. Salir\n";
			std::cin >> raceR;
			if (raceR > 0 && raceR < 6)
			{
				canswerloop = false;

				switch (raceR)
				{
				case 1:
					character.race = BARBAR;
					break;
				case 2:
					character.race = ASSASSIN;
					break;
				case 3:
					character.race = ARCHER;
					break;
				case 4:
					character.race = NIGROMANT;
					break;
				case 5:
					character.race = MAGICIAN;
					break;
				default:
					std::cout << "ERROR AL APLICAR LA RAZA DEL NUEVO PERSONAJE.\n";
					break;
				}
				srand(time(NULL));
				std::cout << "\nNombre del nuevo personaje: ";
				std::cin >> nameR;
				bool CheckNameLoop = true;
				for (size_t i = 0; i < aCharCount; i++)
				{
					if (users[idUser].characters[i].name == nameR)
					{
						std::cout << "Este nombre ya está en uso, por favor introduce otro nombre.";
						std::this_thread::sleep_for(std::chrono::milliseconds(2000));
						system("CLS");
						CheckNameLoop = false;
						canswerloop = true;
					}
				}
				while (CheckNameLoop == true)
				{
					character.name = nameR;
					character.level = 1;

					users[idUser].characters[aCharCount] = character;

					std::cout << "\n\nEl siguiente personaje acaba de ser creado:\n";
					std::cout << "\nNombre: " << character.name;
					std::cout << "\nRaza: ";
					switch (character.race)
					{
					case BARBAR:
						std::cout << "Bárbaro\n";
						break;
					case ASSASSIN:
						std::cout << "Asesino\n";
						break;
					case ARCHER:
						std::cout << "Arquero\n";
						break;
					case NIGROMANT:
						std::cout << "Nigromante\n";
						break;
					case MAGICIAN:
						std::cout << "Hechicero\n";
						break;
					default:
						std::cout << "ERROR AL IMPRIMIR LA RAZA\n";
						break;
					}
					std::cout << "\n\nPulsa Enter para regresar al MENU DE OPCIONES DEL JUGADOR.\n";
					std::cin.get();
					CheckNameLoop = false;
				}
			}
			else if (raceR == 6)
			{
				system("CLS");
				canswerloop = false;
			}
			else
			{
				std::cout << "\nEl  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.\n\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				system("CLS");
			}
		}

	}
}

void ListCharcatersUser()
{
	bool ListCharsLoop = true;
	int aCharCount = aCharactersCount(users[idUser].characters);
	while (ListCharsLoop == true)
	{
		system("CLS");
		int R;
		std::cout << "Lista de personajes.\n";
		if (aCharCount == 0) std::cout << "\nNo hay ningún personaje creado para este usuario.\n";
		else
		{
			for (size_t i = 0; i < aCharCount; i++)
			{
				std::cout << "\n" << i + 1 << ". Nombre: " << users[idUser].characters[i].name << "\n   Raza: ";
				for (size_t j = 0; j < 1; j++)
				{
					switch (users[idUser].characters[i].race)
					{
					case BARBAR:
						std::cout << "Bárbaro\n";
						break;
					case ASSASSIN:
						std::cout << "Asesino\n";
						break;
					case ARCHER:
						std::cout << "Arquero\n";
						break;
					case NIGROMANT:
						std::cout << "Nigromante\n";
						break;
					case MAGICIAN:
						std::cout << "Hechicero\n";
						break;
					default:
						std::cout << "ERROR AL IMPRIMIR LA RAZA\n";
						break;
					}
				}
			}
		}
		std::cout << "\n" << aCharCount + 1 << ". Salir.\n";
		std::cin >> R;
		if (R == aCharCount + 1)
		{
			ListCharsLoop = false;
		}
	}
}

void ListCharactersAdmin()
{
	bool ListCharsLoop = true;
	int usersSize = users.size();
	while (ListCharsLoop)
	{
		system("cls");
		int R;
		std::cout << "Lista de usuarios:\n";
		for (size_t i = 1; i < usersSize; i++)
		{
			std::cout << "\n" << i << ". Nombre de usario: " << users[i].name << "\n";
		}
		std::cout << "\n" << usersSize << ". Salir.\n";
		std::cout << "\nUsuario a consultar: ";
		std::cin >> R;
		system("CLS");
		if (R > 0 && R < usersSize)
		{
			int aCharCount = aCharactersCount(users[R].characters);
			if (aCharCount < 1)
			{
				std::cout << "No hay ningún personaje creado para este usuario.";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
			else
			{
				std::cout << "Lista de personajes.\n";
				for (size_t j = 0; j < aCharCount; j++)
				{
					std::cout << "\n" << j + 1 << ". Nombre: " << users[R].characters[j].name << "\n   Raza: ";
					for (size_t k = 0; k < 1; k++)
					{
						switch (users[R].characters[j].race)
						{
						case BARBAR:
							std::cout << "Bárbaro\n";
							break;
						case ASSASSIN:
							std::cout << "Asesino\n";
							break;
						case ARCHER:
							std::cout << "Arquero\n";
							break;
						case NIGROMANT:
							std::cout << "Nigromante\n";
							break;
						case MAGICIAN:
							std::cout << "Hechicero\n";
							break;
						default:
							std::cout << "ERROR AL IMPRIMIR LA RAZA\n";
							break;
						}
					}
				}
				std::cout << "\n\nPulsa Enter para regresar al listado de usuarios.\n";
				std::cin.get();
				std::cin.ignore();
			}
		}
		else if (R == usersSize)
		{
			system("CLS");
			ListCharsLoop = false;
		}
		else
		{
			std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
			std::cin.get();
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			system("CLS");
		}
	}
}

void DeleteCharacterUser()
{
	bool DeleteCharLoop = true;
	while (DeleteCharLoop == true)
	{
		int aCharCount = aCharactersCount(users[idUser].characters);
		system("CLS");
		if (aCharCount == 0 && DeleteCharLoop)
		{
			std::cout << "No hay ningún personaje creado para este usuario.\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			DeleteCharLoop = false;
		}
		else
		{
			int R;
			std::cout << "Lista de personajes.\n\n";
			for (size_t i = 0; i < aCharCount; i++)
			{
				std::cout << i + 1 << ". " << users[idUser].characters[i].name << std::endl;
			}
			std::cout << "\n" << aCharCount + 1 << ". Salir\n\n";
			std::cout << "Personaje a eliminar: ";
			std::cin >> R;
			if (R == aCharCount + 1) { DeleteCharLoop = false; continue; };
			if (R > 0 && R <= aCharCount)
			{
				char RS;
				std::cout << "Estás seguro de que deseas eliminar el personaje \"" << users[idUser].characters[R - 1].name << "\"? (S/N)";
				std::cin >> RS;
				if (RS == 's' || RS == 'S')
				{
					Character AuxChar;
					for (size_t i = R - 1; i < aCharCount - 1; i++)
					{
						if (i + 1 == 5) continue;
						users[idUser].characters[i] = users[idUser].characters[i+1];
					}
					users[idUser].characters[aCharCount-1] = AuxChar;
				}
				else if (RS == 'n' || RS == 'N') continue;
				else
				{
					std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				}
			}
			else
			{
				std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				system("CLS");
			}
		}
	}
}

void DeleteCharacterAdmin()
{
	bool DeleteCharLoop = true;
	int usersSize = users.size();
	while (DeleteCharLoop)
	{
		system("CLS");
		int R;
		std::cout << "Lista de usuarios:\n\n";
		for (size_t i = 1; i < usersSize; i++)
		{
			std::cout << "\n" << i << ". Nombre de usario: " << users[i].name << "\n";
		}
		std::cout << "\n" << usersSize << ". Salir.\n";
		std::cout << "\nUsuario a consultar: ";
		std::cin >> R;
		system("CLS");
		if (R > 0 && R < usersSize)
		{
			int aCharCount = aCharactersCount(users[R-1].characters);
			bool DeleteCharLoopAux = true;
			while (DeleteCharLoopAux == true)
			{
				int D = 0;
				std::cout << "Lista de personajes.\n\n";
				for (size_t i = 0; i < aCharCount; i++)
				{
					std::cout << i + 1 << ". " << users[R].characters[i].name << std::endl;
				}
				std::cout << aCharCount + 1 << ". Salir\n\n";
				std::cout << "Personaje a eliminar: ";
				std::cin >> D;
				if (D <= aCharCount)
				{
					for (size_t i = D - 1; i < aCharCount - 1; i++)
					{
						users[R].characters[i] = users[R].characters[i + 1];
					}
					std::cout << "Se ha eliminado satisfactoriamente el personaje seleccionado!";
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				}
				else if (D == aCharCount + 1)
				{
					DeleteCharLoopAux = false;
				}
				else
				{
					std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
					system("CLS");
				}
			}
		}
		else if (R == usersSize)
		{
			DeleteCharLoop = false;
		}
		else if (aCharactersCount(users[R].characters) == 0)
		{
			std::cout << "No hay ningún personaje creado para este usuario.\n";
		}
	}
}

void ListUsers()
{
	system("CLS");
	bool ListUsersLoop = true;
	while (ListUsersLoop == true)
	{
		int R;
		std::cout << "Lista de usuarios.\n";
		for (size_t i = 0; i < users.size(); i++)
		{
			int aCharCount = aCharactersCount(users[i].characters);
			if (users[i].admin)
			{
				std::cout << "\n" << i << ". Nombre de usario: " << users[i].name << " - (A)\n";
			}
			else
			{
				std::cout << "\n" << i << ". Nombre de usario: " << users[i].name << "\n";
			}
			if (aCharCount > 0)
			{
				std::cout << "   Personajes: " << aCharCount << ".\n";
			}
		}
		std::cout << "\n" << users.size() << ". Salir.\n";
		std::cin >> R;
		if (R == users.size())
		{
			ListUsersLoop = false;
		}
		else
		{
			std::cout << "El  valor que has introducido no coincide con ninguna opción. Vuelve a intentarlo.";
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			system("CLS");
		}
	}
}
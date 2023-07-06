#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Contato {
    std::string nome;
    std::string telefone;
};

void inserirContato(std::vector<Contato>& agenda) {
    Contato novoContato;
    std::cout << "Digite o nome do contato: ";
    std::cin.ignore();
    std::getline(std::cin, novoContato.nome);
    std::cout << "Digite o telefone do contato: ";
    std::getline(std::cin, novoContato.telefone);
    agenda.push_back(novoContato);
    std::cout << "Contato inserido com sucesso!\n";
}

void listarContatos(const std::vector<Contato>& agenda) {
    if (agenda.empty()) {
        std::cout << "Agenda vazia.\n";
        return;
    }
    std::cout << "Lista de contatos:\n";
    for (const auto& contato : agenda) {
        std::cout << "Nome: " << contato.nome << ", Telefone: " << contato.telefone << "\n";
    }
}

void procurarPorNome(const std::vector<Contato>& agenda) {
    if (agenda.empty()) {
        std::cout << "Agenda vazia.\n";
        return;
    }
    std::string nomeProcurado;
    std::cout << "Digite o nome para procurar: ";
    std::cin.ignore();
    std::getline(std::cin, nomeProcurado);

    bool encontrado = false;
    for (const auto& contato : agenda) {
        if (contato.nome == nomeProcurado) {
            std::cout << "Nome: " << contato.nome << ", Telefone: " << contato.telefone << "\n";
            encontrado = true;
        }
    }
    if (!encontrado) {
        std::cout << "Contato não encontrado.\n";
    }
}

void procurarPorTelefone(const std::vector<Contato>& agenda) {
    if (agenda.empty()) {
        std::cout << "Agenda vazia.\n";
        return;
    }
    std::string telefoneProcurado;
    std::cout << "Digite o telefone para procurar: ";
    std::cin.ignore();
    std::getline(std::cin, telefoneProcurado);

    bool encontrado = false;
    for (const auto& contato : agenda) {
        if (contato.telefone == telefoneProcurado) {
            std::cout << "Nome: " << contato.nome << ", Telefone: " << contato.telefone << "\n";
            encontrado = true;
        }
    }
    if (!encontrado) {
        std::cout << "Contato não encontrado.\n";
    }
}

void alterarContato(std::vector<Contato>& agenda) {
    if (agenda.empty()) {
        std::cout << "Agenda vazia.\n";
        return;
    }
    std::string nomeProcurado;
    std::cout << "Digite o nome do contato a ser alterado: ";
    std::cin.ignore();
    std::getline(std::cin, nomeProcurado);

    auto it = std::find_if(agenda.begin(), agenda.end(), [&](const Contato& contato) {
        return contato.nome == nomeProcurado;
    });

    if (it != agenda.end()) {
        Contato& contato = *it;
        std::cout << "Digite o novo nome do contato: ";
        std::getline(std::cin, contato.nome);
        std::cout << "Digite o novo telefone do contato: ";
        std::getline(std::cin, contato.telefone);
        std::cout << "Contato alterado com sucesso!\n";
    } else {
        std::cout << "Contato não encontrado.\n";
    }
}

void quantidadeContatos(const std::vector<Contato>& agenda) {
    std::cout << "Quantidade de contatos: " << agenda.size() << "\n";
}

void excluirAgenda(std::vector<Contato>& agenda) {
    agenda.clear();
    std::cout << "Agenda excluída.\n";
}

void salvarAgenda(const std::vector<Contato>& agenda) {
    std::ofstream arquivo("agenda.txt");
    if (!arquivo) {
        std::cerr << "Erro ao salvar a agenda.\n";
        return;
    }
    for (const auto& contato : agenda) {
        arquivo << contato.nome << "," << contato.telefone << "\n";
    }
    arquivo.close();
}

void carregarAgenda(std::vector<Contato>& agenda) {
    std::ifstream arquivo("agenda.txt");
    if (!arquivo) {
        std::cerr << "Erro ao carregar a agenda.\n";
        return;
    }
    agenda.clear();
    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::size_t pos = linha.find(",");
        if (pos != std::string::npos) {
            std::string nome = linha.substr(0, pos);
            std::string telefone = linha.substr(pos + 1);
            agenda.push_back({ nome, telefone });
        }
    }
    arquivo.close();
}

int main() {
    std::vector<Contato> agenda;
    carregarAgenda(agenda);

    int opcao = 0;
    while (opcao != 8) {
        std::cout << "\n*** MENU ***\n";
        std::cout << "1 - Inserir um contato na agenda\n";
        std::cout << "2 - Listar todos os contatos\n";
        std::cout << "3 - Procurar por nome\n";
        std::cout << "4 - Procurar por número\n";
        std::cout << "5 - Alterar contato\n";
        std::cout << "6 - Quantidade de contatos\n";
        std::cout << "7 - Excluir Agenda\n";
        std::cout << "8 - Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                inserirContato(agenda);
                salvarAgenda(agenda);
                break;
            case 2:
                listarContatos(agenda);
                break;
            case 3:
                procurarPorNome(agenda);
                break;
            case 4:
                procurarPorTelefone(agenda);
                break;
            case 5:
                alterarContato(agenda);
                salvarAgenda(agenda);
                break;
            case 6:
                quantidadeContatos(agenda);
                break;
            case 7:
                excluirAgenda(agenda);
                salvarAgenda(agenda);
                break;
            case 8:
                std::cout << "Encerrando o programa.\n";
                break;
            default:
                std::cout << "Opção inválida.\n";
                break;
        }
    }

    return 0;
}

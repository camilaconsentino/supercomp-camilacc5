#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// =========================================
// Constantes globais
// =========================================
const size_t N = 100'000'000; // Número total de amostras
const size_t K = 10;          // Tamanho da janela da média móvel

// =========================================
// Função para gerar um vetor com valores aleatórios
// =========================================
vector<double> gerar_leituras(size_t tamanho) {
    // TODO: Criar um vetor de tamanho `tamanho`
    vector<double> v(tamanho);

    // TODO: Criar gerador de números aleatórios com seed fixa
    unsigned seed = 12345; // Seed fixa para reprodutibilidade
    default_random_engine generator(seed);

    // TODO: Definir distribuição entre 12.0 e 189.98
    uniform_real_distribution<double> distribution(12.0, 189.98);
    

    // TODO: Preencher o vetor com números aleatórios
    for (size_t i = 0; i < tamanho; ++i) {
        v[i] = distribution(generator);
    }

    // DICA: use std::vector<double> e uniform_real_distribution

    return v; // Substitua pelo vetor preenchido
}

// =========================================
// Função para calcular a média móvel (passagem por valor)
// =========================================
vector<double> media_movel_por_valor(vector<double> v, size_t K) {
    // TODO: Calcular a média móvel simples sobre o vetor recebido por valor
    size_t tamanho = v.size();
    vector<double> resultado(tamanho-K+1);
    for (size_t i = 0; i <= tamanho - K; ++i) {
        double soma = 0.0;
        for (size_t j = 0; j < K; ++j) {
            soma += v[i + j];
        }
        double media = soma / K;

        // Armazenar ou processar a média conforme necessário
        resultado[i] = media; 
    }
    // TODO: Retornar um vetor com os resultados

    return resultado;
}

// =========================================
// Função para calcular a média móvel (passagem por referência)
// =========================================
vector<double> media_movel_por_referencia(const vector<double>& v, size_t K) {
    // TODO: Igual à versão anterior, mas recebendo os dados por referência constante
    size_t tamanho = v.size();
    vector<double> resultado(tamanho - K + 1);

    for (size_t i = 0; i <= tamanho - K; ++i) {
        double soma = 0.0;
        for (size_t j = 0; j < K; ++j) {
            soma += v[i + j];
        }
        resultado[i] = soma / K;
    }
    return resultado;
}


// =========================================
// Função para calcular a média móvel (passagem por ponteiro)
// =========================================
vector<double> media_movel_por_ponteiro(const double* ptr, size_t tamanho, size_t K) {
    // TODO: Usar aritmética de ponteiros para calcular a média móvel
    // TODO: Retornar um vetor com os resultados
    vector<double> resultado(tamanho - K + 1);

    for (size_t i = 0; i <= tamanho - K; ++i) {
        double soma = 0.0;
        for (size_t j = 0; j < K; ++j) {
            soma += *(ptr + i + j); // ou ptr[i + j]
        }
        resultado[i] = soma / K;
    }
    return resultado;
}

// =========================================
// Função para medir tempo de execução
// =========================================
template <typename Func, typename... Args>
double medir_tempo(Func funcao, Args&&... args) {
    auto inicio = chrono::high_resolution_clock::now();
    funcao(forward<Args>(args)...);
    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> duracao = fim - inicio;
    return duracao.count();
}

// =========================================
// Função principal
// =========================================
int main() {
    // Etapa 1: Gerar os dados
    cout << "Gerando dados..." << endl;
    vector<double> leituras = gerar_leituras(N);
    cout << "Dados gerados: " << leituras.size() << " leituras." << endl;

    // Etapa 2: Cálculo por valor
    cout << "Média móvel (por valor):" << endl;
    double tempo_valor = medir_tempo(media_movel_por_valor, leituras, K);
    cout << "→ Tempo: " << tempo_valor << " s" << endl;

    // Etapa 3: Cálculo por referência
    cout << "Média móvel (por referência):" << endl;
    double tempo_ref = medir_tempo(media_movel_por_referencia, leituras, K);
    cout << "→ Tempo: " << tempo_ref << " s" << endl;

    // Etapa 4: Cálculo por ponteiro
    cout << "Média móvel (por ponteiro):" << endl;
    const double* ptr = leituras.data();
    double tempo_ptr = medir_tempo(media_movel_por_ponteiro, ptr, N, K);
    cout << "→ Tempo: " << tempo_ptr << " s" << endl;

    // Etapa 5: Compile com diferentes flags e compare os tempos
    // Exemplo:
    //   g++ media.cpp -o sem_otimizacao
    //   g++ -O2 media.cpp -o otimizacao_O2
    //   g++ -O3 media.cpp -o otimizacao_O23
    //   g++ -Ofast media.cpp -o otimizacao_Ofast
    return 0;
}
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// Función para calcular TF
double calculateTF(int termFrequency, int totalTerms) {
    return static_cast<double>(termFrequency) / totalTerms;
}

// Función para calcular IDF
double calculateIDF(int totalDocuments, int documentFrequency) {
    if (documentFrequency == 0) return 0;
    return log(static_cast<double>(totalDocuments) / documentFrequency);
}

// Función para calcular TF-IDF
double calculateTFIDF(int termFrequency, int totalTerms, int totalDocuments, int documentFrequency) {
    double tf = calculateTF(termFrequency, totalTerms);
    double idf = calculateIDF(totalDocuments, documentFrequency);
    return tf * idf;
}

int main() {
    // Ejemplo de documentos
    std::vector<std::string> documents = {
        "este es un documento de ejemplo",
        "este documento es otro ejemplo",
        "un tercer documento también es un ejemplo"
    };

    // Mapa para contar la frecuencia de términos
    std::unordered_map<std::string, int> termFrequency;
    int totalDocuments = documents.size();

    // Contar la frecuencia de términos
    for (const auto& doc : documents) {
        std::unordered_map<std::string, int> docTermFrequency;
        std::istringstream stream(doc);
        std::string term;
        
        while (stream >> term) {
            docTermFrequency[term]++;
        }
        
        // Actualizar la frecuencia total
        for (const auto& entry : docTermFrequency) {
            termFrequency[entry.first] += entry.second;
        }
    }

    // Calcular y mostrar TF-IDF para cada término
    std::cout << "TF-IDF para cada término:\n";
    for (const auto& entry : termFrequency) {
        const std::string& term = entry.first;
        int termFreq = entry.second;
        
        // Calcular la frecuencia del documento
        int documentFreq = 0;
        for (const auto& doc : documents) {
            if (doc.find(term) != std::string::npos) {
                documentFreq++;
            }
        }

        double tfidf = calculateTFIDF(termFreq, totalDocuments, totalDocuments, documentFreq);
        std::cout << "Término: " << term << ", TF-IDF: " << tfidf << std::endl;
    }

    return 0;
}

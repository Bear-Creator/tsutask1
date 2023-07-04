#include <iostream>
#include <fstream>

#pragma pack(push, 1)

// Структура заголовка BMP-файла
struct BMPHeader {
    uint16_t signature;   // Сигнатура "BM"
    uint32_t fileSize;    // Размер файла
    uint32_t reserved;    // Зарезервировано (должно быть 0)
    uint32_t dataOffset;  // Смещение данных пикселей
    // Другие поля заголовка (не используем в этом примере)
};

// Структура информации о BMP-изображении
struct BMPInfo {
    uint32_t infoSize;       // Размер структуры информации (должен быть 40)
    int32_t width;           // Ширина изображения в пикселях
    int32_t height;          // Высота изображения в пикселях
    uint16_t planes;         // Количество плоскостей (должно быть 1)
    uint16_t bitsPerPixel;   // Бит на пиксель
    // Другие поля информации (не используем в этом примере)
};

#pragma pack(pop)

void changeColorIntensity(const std::string& filename, int startX, int startY, int endX, int endY, int channel, int intensity) {
    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    BMPHeader header;
    BMPInfo info;

    // Чтение заголовка и информации о изображении
    inputFile.read(reinterpret_cast<char*>(&header), sizeof(header));
    inputFile.read(reinterpret_cast<char*>(&info), sizeof(info));

    if (header.signature != 0x4D42) {
        std::cout << "The file is not a valid BMP image." << std::endl;
        return;
    }

    if (info.bitsPerPixel != 24) {
        std::cout << "Changing color intensity is only supported for 24-bit BMP images." << std::endl;
        return;
    }

    // Проверка допустимости координат
    if (startX < 0 || startY < 0 || startX >= info.width || startY >= info.height ||
        endX < 0 || endY < 0 || endX >= info.width || endY >= info.height) {
        std::cout << "Invalid coordinates for the specified region." << std::endl;
        return;
    }

    // Вычисление размера строки пикселей с выравниванием
    int rowSize = ((info.width * info.bitsPerPixel + 31) / 32) * 4;

    // Перемещение указателя на начало данных пикселей
    inputFile.seekg(header.dataOffset, std::ios::beg);

    // Создание временного файла для записи измененного изображения
    std::string tempFilename = "temp.bmp";
    std::ofstream tempFile(tempFilename, std::ios::binary);
    if (!tempFile) {
        std::cout << "Failed to create a temporary file." << std::endl;
        return;
    }

    // Запись заголовка и информации во временный файл
    tempFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    tempFile.write(reinterpret_cast<const char*>(&info), sizeof(info));

    // Копирование и изменение интенсивности пикселей
    for (int y = 0; y < info.height; y++) {
        for (int x = 0; x < info.width; x++) {
            uint8_t pixel[3];
            inputFile.read(reinterpret_cast<char*>(pixel), sizeof(pixel));

            if (x >= startX && x <= endX && y >= startY && y <= endY) {
                pixel[channel] = std::min(std::max(pixel[channel] + intensity, 0), 255);
            }

            tempFile.write(reinterpret_cast<const char*>(pixel), sizeof(pixel));
        }

        // Пропуск выравнивания
        inputFile.seekg(rowSize - info.width * sizeof(uint8_t) * 3, std::ios::cur);
        tempFile.seekp(rowSize - info.width * sizeof(uint8_t) * 3, std::ios::cur);
    }

    // Закрытие файлов
    inputFile.close();
    tempFile.close();

    // Замена исходного файла измененным файлом
    std::remove(filename.c_str());
    std::rename(tempFilename.c_str(), filename.c_str());

    std::cout << "The image has been successfully modified and saved." << std::endl;
}

int main() {
    std::string filename = "image.bmp";

    // Указание прямоугольной области и изменение интенсивности цвета
    int startX = 100;   // Начальная координата X
    int startY = 100;   // Начальная координата Y
    int endX = 200;     // Конечная координата X
    int endY = 200;     // Конечная координата Y
    int channel = 2;    // Канал (0 - синий, 1 - зеленый, 2 - красный)
    int intensity = 50; // Изменение интенсивности (-255 до 255)

    // Изменение интенсивности цвета в указанной области изображения
    changeColorIntensity(filename, startX, startY, endX, endY, channel, intensity);

    return 0;
}

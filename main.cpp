/*******************************************************************************************
*
*   raylib [textures] example - Load textures from raw data
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.3, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/


//#include "src/app.h"
#include "raylib.h"
#include "iostream"
#include "vector"
#include "src/BlockChain.h"

const int screenWidth = 2000;
const int screenHeight = 1000;
using namespace std;

struct Block {
    int index;
    std::string data;
    std::string previousHash;
    std::string hash;
};
void DrawLoading2() {
    const int fontSize = 24;

    const int animationFrames = 10;  // Número de fotogramas de la animación
    const int frameDuration = 10;   // Duración de cada fotograma en milisegundos

    bool exitLoading = false;

    int currentFrame = 0;
    int dotCount = 0;
    const std::string loadingText = "Loading";

    while (!exitLoading) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(loadingText.c_str(), screenWidth / 2 - MeasureText(loadingText.c_str(), fontSize) / 2, screenHeight / 2, fontSize, WHITE);

        // Generar los puntos de la animación
        std::string dots = "";
        for (int i = 0; i < dotCount; ++i) {
            dots += ".";
        }

        DrawText(dots.c_str(), screenWidth / 2 + MeasureText(loadingText.c_str(), fontSize) / 2 + 10, screenHeight / 2, fontSize, WHITE);

        // Incrementar el contador de fotogramas
        currentFrame++;

        // Cambiar el número de puntos después de cada fotograma
        if (currentFrame % frameDuration == 0) {
            dotCount = (dotCount + 1) % 4;  // Cambia entre 0, 1, 2 y 3
        }

        EndDrawing();

        // Salir del bucle de carga después de que se complete la animación
        if (currentFrame / frameDuration >= animationFrames) {
            exitLoading = true;
        }

        // Esperar el tiempo de un fotograma
        ::_sleep(frameDuration);
    }
}

void drawTransacciones( std::vector<transaccion>& transacciones) {

    const int fontSize = 20;
    const int padding = 85;


    bool exitTransaccion = false;
    while(!exitTransaccion){
        BeginDrawing();
        ClearBackground(BLACK);
        int x = padding;
        int y = padding;
        int maxLineWidth = screenWidth - padding * 2;
        int i = 1;
        for ( auto & transaccion : transacciones) {
            std::string transaccionInfo = "Transaccion " + std::to_string(i) + ":\n";
            transaccionInfo += "Block ID: " + std::to_string(transaccion.id_bloque) + "\n";
            transaccionInfo += "Monto: " + std::to_string(transaccion.monto) + "\n";
            transaccionInfo += "Emisor: " + transaccion.emisor+ "\n";
            transaccionInfo += "Receptor: " + transaccion.receptor + "\n";
            transaccionInfo += "Fecha: " + std::to_string(transaccion.fechatransaccion.dia) + "/" + std::to_string(transaccion.fechatransaccion.mes) + "/" + std::to_string(transaccion.fechatransaccion.anio);

            int textWidth = MeasureText(transaccionInfo.c_str(), fontSize);
            int textHeight = fontSize * 5; // Estimación del alto del texto

            // Verificar si el texto se desborda horizontalmente
            if (x + textWidth > screenWidth - padding) {
                x = padding;
                y += textHeight + padding;
            }

            DrawText(transaccionInfo.c_str(), x, y-40, fontSize, WHITE);

            x += textWidth + padding;
            i++;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            exitTransaccion = true;
        }
        EndDrawing();
    }

}
void DrawBlocks_index(bool visible, blockchain& bchain,const vector<int>& indices) {
    if (!visible) {
        return;
    }
    Texture2D image = LoadTexture("../assets/bloque.png");  // Reemplaza "image.png" con el nombre de tu imagen
    Texture2D image2 = LoadTexture("../assets/bloque_alterado.png");  // Reemplaza "image.png" con el nombre de tu imagen

    Font customFont = LoadFont("../fonts/VCR_OSD_MONO.ttf");
    const int blockWidth = 800;
    const int blockHeight = 120;
    const int padding = 20;



    const int blocksPerRow = screenWidth / (blockWidth + padding);

    int startX = (screenWidth - (blocksPerRow * (blockWidth + padding) - padding)) / 2;
    int startY = padding;


    bool exitblock = false;
    while (!exitblock){
        BeginDrawing();
        ClearBackground(BLACK);
        int x = startX;
        int y = startY;

        // Dibuja los bloques
        for(auto a: indices){
            auto block = bchain.find_block(a);
            if (block->valido){
                DrawTexture(image, x, y, WHITE);

//            DrawRectangle(x, y, blockWidth, blockHeight, GREEN);
            }
            else{
                DrawTexture(image2, x, y, WHITE);

//            DrawRectangle(x, y, blockWidth, blockHeight, RED);
            }
            string id_visual = "BLOQUE: " + to_string(block->id);
            string nonce = "nonce: " + to_string(block->nonce);
            string prevHash_visual = "prev_hash: " + block->prev_hash;
            string currentHash_visual = "current_hash: " + block->current_hash;
            DrawText(id_visual.c_str(), x + 350, y + 2, 20, WHITE);
            DrawText(nonce.c_str(), x + 10, y + 35, 20, WHITE);
            DrawTextEx(customFont, prevHash_visual.c_str(), { static_cast<float>(x + 10), static_cast<float>(y + 64) }, 15, 0, WHITE);
            DrawTextEx(customFont, currentHash_visual.c_str(), { static_cast<float>(x + 10), static_cast<float>(y + 94) }, 15, 0, WHITE);

            x += blockWidth + padding;

            if (x >= startX + blocksPerRow * (blockWidth + padding)) {
                x = startX;
                y += blockHeight + padding;
            }

        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            exitblock = true;
        }

        EndDrawing();
    }

}

void drawOption1(blockchain& alfa){
    const int fontSize = 50;
    const int inputBoxWidth = 250;
    const int inputBoxHeight = 50;
    const int menuOptionsCount = 4;
    bool enterKeyPressed = false;
    std::string inputText;
    int selectedOption = 0;
    std::string options[menuOptionsCount] = { "Emisor", "Receptor", "Monto", "Fecha" };
    Texture2D image = LoadTexture("../assets/sakura2.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!enterKeyPressed) {
        if (IsKeyPressed(KEY_LEFT)) {
            selectedOption = (selectedOption - 1 + menuOptionsCount) % menuOptionsCount;
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            selectedOption = (selectedOption + 1) % menuOptionsCount;
        }


        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 0){
                string data = inputText;
                std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
                    return std::tolower(c);
                });
                auto v = alfa.search(data,emisor);
                DrawLoading2();
                if (!v.empty()){
                    drawTransacciones(v);
                }
                for(const auto& a: v){
                    a.display();
                }
            }
            else if (selectedOption == 1){
                string data = inputText;
                std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
                    return std::tolower(c);
                });
                auto v = alfa.search(data,receptor);
                DrawLoading2();
                if (!v.empty()){
                    drawTransacciones(v);
                }
            }
            else if (selectedOption == 2){
                double monto_ = std::stod(inputText);
                auto v = alfa.search(monto_);
                DrawLoading2();
                if (!v.empty()){
                    drawTransacciones(v);
                }
            }
            else if (selectedOption == 3){
                auto v = alfa.search(inputText,fechaX);
                DrawLoading2();
                if (!v.empty()){
                    drawTransacciones(v);
                }
            }
            cout << inputText << endl;
            inputText.clear();
        }


        if (IsKeyPressed(KEY_ESCAPE)) {
            enterKeyPressed = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);

        if (selectedOption >= 0 && selectedOption < menuOptionsCount) {
            DrawText("<", screenWidth / 2 - MeasureText(options[selectedOption].c_str(), fontSize) - 100, 200, fontSize, GREEN);
            DrawText(options[selectedOption].c_str(), screenWidth / 2 - MeasureText(options[selectedOption].c_str(), fontSize) / 2, 200, fontSize, GREEN);
            DrawText(">", screenWidth / 2 + MeasureText(options[selectedOption].c_str(), fontSize) + 100, 200, fontSize, GREEN);
        }

        // Dibuja el recuadro de entrada de texto
        DrawRectangle(screenWidth / 2 - inputBoxWidth / 2 , 250, inputBoxWidth, inputBoxHeight, GRAY);
        DrawRectangleLines(screenWidth / 2 - inputBoxWidth / 2 , 250, inputBoxWidth, inputBoxHeight, DARKGRAY);
        DrawText(inputText.c_str(), screenWidth / 2 - MeasureText(inputText.c_str(), fontSize) / 2 , 255, fontSize, BLACK);

        EndDrawing();

        // Captura la entrada del usuario
        int key = GetKeyPressed();
        if ((key >= 32) && (key <= 125)) {
            inputText.push_back(static_cast<char>(key));
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!inputText.empty()) {
                inputText.pop_back();
            }
        }
    }
    UnloadTexture(image);
}
enum class campoActivo2
{
    Monto,
    Fecha
};
void drawOption1_index(blockchain& alfa){
    const int fontSize = 50;
    const int inputBoxWidth = 250;
    const int inputBoxHeight = 50;
    const int menuOptionsCount = 4;
    bool enterKeyPressed = false;
    std::string inputText;
    int selectedOption = 0;
    std::string options[menuOptionsCount] = { "Emisor", "Receptor", "Monto", "Fecha" };
    Texture2D image = LoadTexture("../assets/sakura2.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!enterKeyPressed) {
        if (IsKeyPressed(KEY_LEFT)) {
            selectedOption = (selectedOption - 1 + menuOptionsCount) % menuOptionsCount;
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            selectedOption = (selectedOption + 1) % menuOptionsCount;
        }


        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 0){
                string data = inputText;
                std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
                    return std::tolower(c);
                });
                auto v = alfa.search(data,emisor);
                DrawLoading2();
                auto indices = alfa.get_block_id_from_transaction(v);
                if (!indices.empty()){
                    DrawBlocks_index(true,alfa,indices);
                }
            }
            else if (selectedOption == 1){
                string data = inputText;
                std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
                    return std::tolower(c);
                });
                auto v = alfa.search(data,receptor);
                DrawLoading2();
                auto indices = alfa.get_block_id_from_transaction(v);
                if (!indices.empty()){
                    DrawBlocks_index(true,alfa,indices);
                }
            }
            else if (selectedOption == 2){
                double monto_ = std::stod(inputText);
                auto v = alfa.search(monto_);
                DrawLoading2();
                auto indices = alfa.get_block_id_from_transaction(v);
                if (!indices.empty()){
                    DrawBlocks_index(true,alfa,indices);
                }
            }
            else if (selectedOption == 3){
                auto v = alfa.search(inputText,fechaX);
                DrawLoading2();
                auto indices = alfa.get_block_id_from_transaction(v);
                if (!indices.empty()){
                    DrawBlocks_index(true,alfa,indices);
                }
            }
            cout << inputText << endl;
            inputText.clear();
        }


        if (IsKeyPressed(KEY_ESCAPE)) {
            enterKeyPressed = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);

        if (selectedOption >= 0 && selectedOption < menuOptionsCount) {
            DrawText("<", screenWidth / 2 - MeasureText(options[selectedOption].c_str(), fontSize) - 100, 200, fontSize, GREEN);
            DrawText(options[selectedOption].c_str(), screenWidth / 2 - MeasureText(options[selectedOption].c_str(), fontSize) / 2, 200, fontSize, GREEN);
            DrawText(">", screenWidth / 2 + MeasureText(options[selectedOption].c_str(), fontSize) + 100, 200, fontSize, GREEN);
        }

        // Dibuja el recuadro de entrada de texto
        DrawRectangle(screenWidth / 2 - inputBoxWidth / 2 , 250, inputBoxWidth, inputBoxHeight, GRAY);
        DrawRectangleLines(screenWidth / 2 - inputBoxWidth / 2 , 250, inputBoxWidth, inputBoxHeight, DARKGRAY);
        DrawText(inputText.c_str(), screenWidth / 2 - MeasureText(inputText.c_str(), fontSize) / 2 , 255, fontSize, BLACK);

        EndDrawing();

        // Captura la entrada del usuario
        int key = GetKeyPressed();
        if ((key >= 32) && (key <= 125)) {
            inputText.push_back(static_cast<char>(key));
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!inputText.empty()) {
                inputText.pop_back();
            }
        }
    }
    UnloadTexture(image);
}
void drawOption2(bool isOption2,blockchain& alfa){
    const int fontSize = 50;
    char inputIndexBloque[32] = {0};
    char inputIndexTransaccion[32] = {0};
    const int inputBoxWidth = 250;
    const int inputBoxHeight = 50;
    bool enterKeyPressed = false;
    campoActivo2 campoActivo = campoActivo2::Monto;
    string resultado;
    double startTime = GetTime(); // Tiempo de inicio del mensaje
    double intervalo = 2.0; // Duración del mensaje en segundos
    const int menuOptionsCountH = 2;
    int selectedOptionH = 0;
    std::string options[menuOptionsCountH] = {"Monto", "Fecha" };
    Texture2D image = LoadTexture("../assets/sakura2.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!enterKeyPressed) {
        if (IsKeyPressed(KEY_LEFT)) {
            selectedOptionH = (selectedOptionH - 1 + menuOptionsCountH) % menuOptionsCountH;
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            selectedOptionH = (selectedOptionH + 1) % menuOptionsCountH;
        }
        if (IsKeyPressed(KEY_UP)) {
            if (campoActivo == campoActivo2::Fecha) {
                campoActivo = campoActivo2::Monto;
            }else if (campoActivo == campoActivo2::Monto) {
                campoActivo = campoActivo2::Fecha;
            }
        }

        if (IsKeyPressed(KEY_DOWN)) {
            if (campoActivo == campoActivo2::Monto) {
                campoActivo = campoActivo2::Fecha;
            }else if (campoActivo == campoActivo2::Fecha) {
                campoActivo = campoActivo2::Monto;
            }
        }
        if (isOption2 && IsKeyPressed(KEY_ENTER)) {
            std::string value1(inputIndexBloque);
            std::string value2(inputIndexTransaccion);
            if (value1.empty() || value2.empty()){
                resultado = "Registro erroneo";
                startTime = GetTime(); // Reiniciar el tiempo de inicio cuando se muestra el mensaje

            }
            else{
                if (selectedOptionH == 0){
                    double monto1_ = std::stod(value1);
                    double monto2_ = std::stod(value2);
                    cout << "monto1:" << monto1_;
                    cout << "monto2:" << monto2_;

                    auto v = alfa.transaction_range_search_monto(monto1_,monto2_);
                    DrawLoading2();
                    if (!v.empty()){
                        drawTransacciones(v);
                    }
                }
                else if (selectedOptionH == 1){
                    auto v = alfa.transaction_range_search_fecha(value1,value2);
                    DrawLoading2();
                    if (!v.empty()){
                        drawTransacciones(v);
                    }
                }
            }

            memset(inputIndexBloque, 0, sizeof(inputIndexBloque));
            memset(inputIndexTransaccion, 0, sizeof(inputIndexTransaccion));
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            enterKeyPressed = true;
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            switch (campoActivo)
            {
                case campoActivo2::Monto:
                {
                    int lengthIndexBloque = strlen(inputIndexBloque);
                    if (lengthIndexBloque > 0)
                        inputIndexBloque[lengthIndexBloque - 1] = '\0';
                }
                    break;
                case campoActivo2::Fecha:
                {
                    int lengthIndexTransaccion = strlen(inputIndexTransaccion);
                    if (lengthIndexTransaccion > 0)
                        inputIndexTransaccion[lengthIndexTransaccion - 1] = '\0';
                }
                    break;
            }
        }
        else
        {
            switch (campoActivo)
            {
                case campoActivo2::Monto:
                {
                    int lengthIndexBloque = strlen(inputIndexBloque);
                    if (lengthIndexBloque < sizeof(inputIndexBloque) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputIndexBloque[lengthIndexBloque] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case campoActivo2::Fecha:
                {
                    int lengthIndexTransaccion = strlen(inputIndexTransaccion);
                    if (lengthIndexTransaccion < sizeof(inputIndexTransaccion) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputIndexTransaccion[lengthIndexTransaccion] = static_cast<char>(key);
                        }
                    }
                }
                    break;
            }
        }


        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);

        if (selectedOptionH >= 0 && selectedOptionH < menuOptionsCountH) {
            DrawText("<", screenWidth / 2 - MeasureText(options[selectedOptionH].c_str(), fontSize) - 100, 200, fontSize, GREEN);
            DrawText(options[selectedOptionH].c_str(), screenWidth / 2 - MeasureText(options[selectedOptionH].c_str(), fontSize) / 2, 200, fontSize, GREEN);
            DrawText(">", screenWidth / 2 + MeasureText(options[selectedOptionH].c_str(), fontSize) + 100, 200, fontSize, GREEN);
        }

        // Dibuja los recuadros de entrada de texto
        DrawText("index_bloque:", 700, 460, 20, DARKGRAY);
        DrawRectangle(900, 460, 200, 30, campoActivo == campoActivo2::Monto ? SKYBLUE : LIGHTGRAY);
        DrawText(inputIndexBloque, 930, 465, 20, GRAY);

        DrawText("index_transaccion:", 700, 500, 20, DARKGRAY);
        DrawRectangle(900, 500, 200, 30, campoActivo == campoActivo2::Fecha ? SKYBLUE : LIGHTGRAY);
        DrawText(inputIndexTransaccion, 930, 505, 20, GRAY);
        if (GetTime() - startTime < intervalo) {
            DrawText(resultado.c_str(), 830, 650, 30, RED);
        }
        EndDrawing();
    }
    UnloadTexture(image);
}
void drawOption2_index(bool isOption2,blockchain& alfa){
    const int fontSize = 50;
    char inputIndexBloque[32] = {0};
    char inputIndexTransaccion[32] = {0};
    const int inputBoxWidth = 250;
    const int inputBoxHeight = 50;
    bool enterKeyPressed = false;
    campoActivo2 campoActivo = campoActivo2::Monto;
    string resultado;
    double startTime = GetTime(); // Tiempo de inicio del mensaje
    double intervalo = 2.0; // Duración del mensaje en segundos
    const int menuOptionsCountH = 2;
    int selectedOptionH = 0;
    std::string options[menuOptionsCountH] = {"Monto", "Fecha" };
    Texture2D image = LoadTexture("../assets/sakura2.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!enterKeyPressed) {
        if (IsKeyPressed(KEY_LEFT)) {
            selectedOptionH = (selectedOptionH - 1 + menuOptionsCountH) % menuOptionsCountH;
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            selectedOptionH = (selectedOptionH + 1) % menuOptionsCountH;
        }
        if (IsKeyPressed(KEY_UP)) {
            if (campoActivo == campoActivo2::Fecha) {
                campoActivo = campoActivo2::Monto;
            }else if (campoActivo == campoActivo2::Monto) {
                campoActivo = campoActivo2::Fecha;
            }
        }

        if (IsKeyPressed(KEY_DOWN)) {
            if (campoActivo == campoActivo2::Monto) {
                campoActivo = campoActivo2::Fecha;
            }else if (campoActivo == campoActivo2::Fecha) {
                campoActivo = campoActivo2::Monto;
            }
        }
        if (isOption2 && IsKeyPressed(KEY_ENTER)) {
            std::string value1(inputIndexBloque);
            std::string value2(inputIndexTransaccion);
            if (value1.empty() || value2.empty()){
                resultado = "Registro erroneo";
                startTime = GetTime(); // Reiniciar el tiempo de inicio cuando se muestra el mensaje

            }
            else{
                if (selectedOptionH == 0){
                    double monto1_ = std::stod(value1);
                    double monto2_ = std::stod(value2);
                    cout << "monto1:" << monto1_;
                    cout << "monto2:" << monto2_;

                    auto v = alfa.transaction_range_search_monto(monto1_,monto2_);
                    DrawLoading2();
                    auto indices = alfa.get_block_id_from_transaction(v);
                    if (!indices.empty()){
                        DrawBlocks_index(true,alfa,indices);
                    }
                }
                else if (selectedOptionH == 1){
                    auto v = alfa.transaction_range_search_fecha(value1,value2);
                    DrawLoading2();
                    auto indices = alfa.get_block_id_from_transaction(v);
                    if (!indices.empty()){
                        DrawBlocks_index(true,alfa,indices);
                    }
                }
            }

            memset(inputIndexBloque, 0, sizeof(inputIndexBloque));
            memset(inputIndexTransaccion, 0, sizeof(inputIndexTransaccion));
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            enterKeyPressed = true;
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            switch (campoActivo)
            {
                case campoActivo2::Monto:
                {
                    int lengthIndexBloque = strlen(inputIndexBloque);
                    if (lengthIndexBloque > 0)
                        inputIndexBloque[lengthIndexBloque - 1] = '\0';
                }
                    break;
                case campoActivo2::Fecha:
                {
                    int lengthIndexTransaccion = strlen(inputIndexTransaccion);
                    if (lengthIndexTransaccion > 0)
                        inputIndexTransaccion[lengthIndexTransaccion - 1] = '\0';
                }
                    break;
            }
        }
        else
        {
            switch (campoActivo)
            {
                case campoActivo2::Monto:
                {
                    int lengthIndexBloque = strlen(inputIndexBloque);
                    if (lengthIndexBloque < sizeof(inputIndexBloque) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputIndexBloque[lengthIndexBloque] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case campoActivo2::Fecha:
                {
                    int lengthIndexTransaccion = strlen(inputIndexTransaccion);
                    if (lengthIndexTransaccion < sizeof(inputIndexTransaccion) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputIndexTransaccion[lengthIndexTransaccion] = static_cast<char>(key);
                        }
                    }
                }
                    break;
            }
        }


        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);

        if (selectedOptionH >= 0 && selectedOptionH < menuOptionsCountH) {
            DrawText("<", screenWidth / 2 - MeasureText(options[selectedOptionH].c_str(), fontSize) - 100, 200, fontSize, GREEN);
            DrawText(options[selectedOptionH].c_str(), screenWidth / 2 - MeasureText(options[selectedOptionH].c_str(), fontSize) / 2, 200, fontSize, GREEN);
            DrawText(">", screenWidth / 2 + MeasureText(options[selectedOptionH].c_str(), fontSize) + 100, 200, fontSize, GREEN);
        }

        // Dibuja los recuadros de entrada de texto
        DrawText("index_bloque:", 700, 460, 20, DARKGRAY);
        DrawRectangle(900, 460, 200, 30, campoActivo == campoActivo2::Monto ? SKYBLUE : LIGHTGRAY);
        DrawText(inputIndexBloque, 930, 465, 20, GRAY);

        DrawText("index_transaccion:", 700, 500, 20, DARKGRAY);
        DrawRectangle(900, 500, 200, 30, campoActivo == campoActivo2::Fecha ? SKYBLUE : LIGHTGRAY);
        DrawText(inputIndexTransaccion, 930, 505, 20, GRAY);
        if (GetTime() - startTime < intervalo) {
            DrawText(resultado.c_str(), 830, 650, 30, RED);
        }
        EndDrawing();
    }
    UnloadTexture(image);
}
void drawOptions3(bool isDrawOption, blockchain& alfa){
    const int fontSize = 50;
    const int inputBoxWidth = 250;
    const int inputBoxHeight = 50;
    const int menuOptionsCount = 4;
    bool enterKeyPressed = false;
    std::string inputText;
    int selectedOption = 0;
    Texture2D image = LoadTexture("../assets/sakura2.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!enterKeyPressed) {
        if (IsKeyPressed(KEY_ENTER)) {
            string data = inputText;
            std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
                return std::tolower(c);
            });
            auto v = alfa.start_with(data);
            auto temp1 = alfa.get_block_id_from_user(v);
            vector<transaccion> transacciones;
            for(auto a : temp1){
                auto temp2 = alfa.find_block(a);
                auto temp3 = temp2->getTransaccion();
                for(const auto& z:temp3){
                    transacciones.push_back(z);
                }
            }
            drawTransacciones(transacciones);
            inputText.clear();
        }


        if (IsKeyPressed(KEY_ESCAPE)) {
            enterKeyPressed = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Blockchain", screenWidth / 2 - MeasureText("Blockchain", 200) / 2, 100, 200, WHITE);

        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);
        DrawText("Buscar palabra que empieza con:", 500, 500, 30, WHITE);



        // Dibuja el recuadro de entrada de texto
        DrawRectangle(500, 555, 1000, 40,  LIGHTGRAY);
        DrawText(inputText.c_str(), 530, 560, 40, GRAY);

        EndDrawing();

        // Captura la entrada del usuario
        int key = GetKeyPressed();
        if ((key >= 32) && (key <= 125)) {
            inputText.push_back(static_cast<char>(key));
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!inputText.empty()) {
                inputText.pop_back();
            }
        }
    }
    UnloadTexture(image);
}

void drawOptions3_block(bool isDrawOption, blockchain& alfa){
    const int fontSize = 50;
    const int inputBoxWidth = 250;
    const int inputBoxHeight = 50;
    const int menuOptionsCount = 4;
    bool enterKeyPressed = false;
    std::string inputText;
    int selectedOption = 0;
    // BLOQUE DRAW:
    Font customFont = LoadFont("../fonts/VCR_OSD_MONO.ttf");
    const int blockWidth = 800;
    const int blockHeight = 120;
    const int padding = 20;



    const int blocksPerRow = screenWidth / (blockWidth + padding);

    int startX = (screenWidth - (blocksPerRow * (blockWidth + padding) - padding)) / 2;
    int startY = padding;

    Texture2D image2 = LoadTexture("../assets/bloque.png");  // Reemplaza "image.png" con el nombre de tu imagen
    Texture2D image3 = LoadTexture("../assets/bloque_alterado.png");  // Reemplaza "image.png" con el nombre de tu imagen
    Texture2D image = LoadTexture("../assets/sakura2.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!enterKeyPressed) {
        int x = startX;
        int y = startY;
        if (IsKeyPressed(KEY_ENTER)) {
            string data = inputText;
            std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
                return std::tolower(c);
            });
            auto v = alfa.start_with(data);
            auto temp1 = alfa.get_block_id_from_user(v);
            cout << "INDEX" << endl;
            for (auto z:temp1){
                cout <<"index:" << z << endl;
            }
            DrawBlocks_index(true,alfa,temp1);
            cout << "string" << endl;
            cout <<"data:" << data << endl;

            for (auto z1:v){
                cout <<"string:" << z1 << endl;
            }
            cout << "INDEX" << endl;
            for (auto z:temp1){
                cout <<"index:" << z << endl;
            }
        }


        if (IsKeyPressed(KEY_ESCAPE)) {
            enterKeyPressed = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Blockchain", screenWidth / 2 - MeasureText("Blockchain", 200) / 2, 100, 200, WHITE);

        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);
        DrawText("Buscar palabra que empieza con:", 500, 500, 30, WHITE);



        // Dibuja el recuadro de entrada de texto
        DrawRectangle(500, 555, 1000, 40,  LIGHTGRAY);
        DrawText(inputText.c_str(), 530, 560, 40, GRAY);

        EndDrawing();

        // Captura la entrada del usuario
        int key = GetKeyPressed();
        if ((key >= 32) && (key <= 125)) {
            inputText.push_back(static_cast<char>(key));
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!inputText.empty()) {
                inputText.pop_back();
            }
        }
    }
    UnloadTexture(image);
}
void drawOptions4_index(bool isDrawOption, blockchain& alfa){
    const int fontSize = 50;
    const int inputBoxWidth = 250;
    const int inputBoxHeight = 50;
    const int menuOptionsCount = 4;
    bool enterKeyPressed = false;
    std::string inputText;
    int selectedOption = 0;
    Texture2D image = LoadTexture("../assets/sakura2.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!enterKeyPressed) {
        if (IsKeyPressed(KEY_ENTER)) {
            string data = inputText;
            std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
                return std::tolower(c);
            });
            auto v = alfa.contains(data);
            auto temp1 = alfa.get_block_id_from_user(v);
            DrawBlocks_index(true,alfa,temp1);
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            enterKeyPressed = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Blockchain", screenWidth / 2 - MeasureText("Blockchain", 200) / 2, 100, 200, WHITE);

        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);
        DrawText("Buscar palabra que contiene:", 500, 500, 30, WHITE);



        // Dibuja el recuadro de entrada de texto
        DrawRectangle(500, 555, 1000, 40,  LIGHTGRAY);
        DrawText(inputText.c_str(), 530, 560, 40, GRAY);

        EndDrawing();

        // Captura la entrada del usuario
        int key = GetKeyPressed();
        if ((key >= 32) && (key <= 125)) {
            inputText.push_back(static_cast<char>(key));
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!inputText.empty()) {
                inputText.pop_back();
            }
        }
    }
    UnloadTexture(image);
}


void drawOptions4(bool isDrawOption, blockchain& alfa){
    const int fontSize = 50;
    const int inputBoxWidth = 250;
    const int inputBoxHeight = 50;
    const int menuOptionsCount = 4;
    bool enterKeyPressed = false;
    std::string inputText;
    int selectedOption = 0;
    Texture2D image = LoadTexture("../assets/sakura2.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!enterKeyPressed) {
        if (IsKeyPressed(KEY_ENTER)) {
            string data = inputText;
            std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) {
                return std::tolower(c);
            });
            auto v = alfa.contains(data);
            auto temp1 = alfa.get_block_id_from_user(v);
            vector<transaccion> transacciones;
            for(auto a : temp1){
                auto temp2 = alfa.find_block(a);
                auto temp3 = temp2->getTransaccion();
                for(const auto& z:temp3){
                    transacciones.push_back(z);
                }
            }
            drawTransacciones(transacciones);
            inputText.clear();
        }


        if (IsKeyPressed(KEY_ESCAPE)) {
            enterKeyPressed = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Blockchain", screenWidth / 2 - MeasureText("Blockchain", 200) / 2, 100, 200, WHITE);

        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);
        DrawText("Buscar palabra que contiene:", 500, 500, 30, WHITE);



        // Dibuja el recuadro de entrada de texto
        DrawRectangle(500, 555, 1000, 40,  LIGHTGRAY);
        DrawText(inputText.c_str(), 530, 560, 40, GRAY);

        EndDrawing();

        // Captura la entrada del usuario
        int key = GetKeyPressed();
        if ((key >= 32) && (key <= 125)) {
            inputText.push_back(static_cast<char>(key));
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!inputText.empty()) {
                inputText.pop_back();
            }
        }
    }
    UnloadTexture(image);
}

enum class CampoActivo
{
    IndexBloque,
    IndexTransaccion,
    Valor,
    Cambio
};
void DrawAlterar(blockchain& alfa,bool& shouldExit, bool& shouldMenu){
    char inputIndexBloque[32] = {0};
    char inputIndexTransaccion[32] = {0};
    char inputValor[32] = {0};
    char inputCambio[32] = {0};
    string resultado;
    CampoActivo campoActivo = CampoActivo::IndexBloque;
    bool exitDraw = false;
    bool erroneo = false;
    double startTime = GetTime(); // Tiempo de inicio del mensaje
    double intervalo = 2.0; // Duración del mensaje en segundos
    Texture2D image = LoadTexture("../assets/KON_copi.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!exitDraw)
    {
        DrawText("Blockchain", screenWidth / 2 - MeasureText("Blockchain", 200) / 2, 100, 200, WHITE);
        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);
        if (IsKeyPressed(KEY_ENTER))
        {
            std::string indexBloqueBuscado(inputIndexBloque);
            std::string indexTransaccionBuscado(inputIndexTransaccion);
            std::string valorBuscado(inputValor);
            std::string cambioBuscado(inputCambio);
            if (cambioBuscado.empty() || valorBuscado.empty() || indexBloqueBuscado.empty() || indexTransaccionBuscado.empty()){
                resultado = "Registro erroneo";
                startTime = GetTime(); // Reiniciar el tiempo de inicio cuando se muestra el mensaje

            }

            else{
                int bloqueindex = int(std::stod(indexBloqueBuscado));
                int transaccionindex= int(std::stod(indexTransaccionBuscado));
                if (cambioBuscado == "EMISOR"){
                    cout << "EMISOR" << endl;
                    alfa.edit_block(bloqueindex,transaccionindex,valorBuscado, true);
                }
                else if (cambioBuscado == "RECEPTOR"){
                    cout << "RECEPTOR" << endl;
                    alfa.edit_block(bloqueindex,transaccionindex,valorBuscado, false);
                }
                else if (cambioBuscado == "MONTO"){
                    cout << "MONTO" << endl;
                    double monto = std::stod(valorBuscado);
                    alfa.edit_block(bloqueindex,transaccionindex,monto);
                }
                exitDraw = true;

                shouldMenu = true;
            }


            memset(inputIndexBloque, 0, sizeof(inputIndexBloque));
            memset(inputIndexTransaccion, 0, sizeof(inputIndexTransaccion));
            memset(inputValor, 0, sizeof(inputValor));
            memset(inputCambio, 0, sizeof(inputCambio));


        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            shouldMenu = true;
            exitDraw = true;
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            switch (campoActivo)
            {
                case CampoActivo::IndexBloque:
                {
                    int lengthIndexBloque = strlen(inputIndexBloque);
                    if (lengthIndexBloque > 0)
                        inputIndexBloque[lengthIndexBloque - 1] = '\0';
                }
                    break;
                case CampoActivo::IndexTransaccion:
                {
                    int lengthIndexTransaccion = strlen(inputIndexTransaccion);
                    if (lengthIndexTransaccion > 0)
                        inputIndexTransaccion[lengthIndexTransaccion - 1] = '\0';
                }
                    break;
                case CampoActivo::Valor:
                {
                    int lengthValor = strlen(inputValor);
                    if (lengthValor > 0)
                        inputValor[lengthValor - 1] = '\0';
                }
                    break;
                case CampoActivo::Cambio:
                {
                    int lengthCambio = strlen(inputCambio);
                    if (lengthCambio > 0)
                        inputCambio[lengthCambio - 1] = '\0';
                }
                    break;
            }
        }
        else
        {
            switch (campoActivo)
            {
                case CampoActivo::IndexBloque:
                {
                    int lengthIndexBloque = strlen(inputIndexBloque);
                    if (lengthIndexBloque < sizeof(inputIndexBloque) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputIndexBloque[lengthIndexBloque] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case CampoActivo::IndexTransaccion:
                {
                    int lengthIndexTransaccion = strlen(inputIndexTransaccion);
                    if (lengthIndexTransaccion < sizeof(inputIndexTransaccion) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputIndexTransaccion[lengthIndexTransaccion] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case CampoActivo::Valor:
                {
                    int lengthValor = strlen(inputValor);
                    if (lengthValor < sizeof(inputValor) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputValor[lengthValor] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case CampoActivo::Cambio:
                {
                    int lengthCambio = strlen(inputCambio);
                    if (lengthCambio < sizeof(inputCambio) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputCambio[lengthCambio] = static_cast<char>(key);
                        }
                    }
                }
                    break;
            }
        }

        if (IsKeyPressed(KEY_UP))
        {
            switch (campoActivo)
            {
                case CampoActivo::IndexBloque:
                    campoActivo = CampoActivo::Cambio;
                    break;
                case CampoActivo::IndexTransaccion:
                    campoActivo = CampoActivo::IndexBloque;
                    break;
                case CampoActivo::Valor:
                    campoActivo = CampoActivo::IndexTransaccion;
                    break;
                case CampoActivo::Cambio:
                    campoActivo = CampoActivo::Valor;
                    break;
            }
        }

        if (IsKeyPressed(KEY_DOWN))
        {
            switch (campoActivo)
            {
                case CampoActivo::IndexBloque:
                    campoActivo = CampoActivo::IndexTransaccion;
                    break;
                case CampoActivo::IndexTransaccion:
                    campoActivo = CampoActivo::Valor;
                    break;
                case CampoActivo::Valor:
                    campoActivo = CampoActivo::Cambio;
                    break;
                case CampoActivo::Cambio:
                    campoActivo = CampoActivo::IndexBloque;
                    break;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("index_bloque:", 700, 460, 20, DARKGRAY);
        DrawRectangle(900, 460, 200, 30, campoActivo == CampoActivo::IndexBloque ? SKYBLUE : LIGHTGRAY);
        DrawText(inputIndexBloque, 930, 465, 20, GRAY);

        DrawText("index_transaccion:", 700, 500, 20, DARKGRAY);
        DrawRectangle(900, 500, 200, 30, campoActivo == CampoActivo::IndexTransaccion ? SKYBLUE : LIGHTGRAY);
        DrawText(inputIndexTransaccion, 930, 505, 20, GRAY);

        DrawText("valor:    ", 700, 540, 20, DARKGRAY);
        DrawRectangle(900, 540, 200, 30, campoActivo == CampoActivo::Valor ? SKYBLUE : LIGHTGRAY);
        DrawText(inputValor, 930, 545, 20, GRAY);

        DrawText("cambio:", 700, 580, 20, DARKGRAY);
        DrawRectangle(900, 580, 200, 30, campoActivo == CampoActivo::Cambio ? SKYBLUE : LIGHTGRAY);
        DrawText(inputCambio, 930, 585, 20, GRAY);

        DrawText("Resultado:", 800, 620, 20, DARKGRAY);
//        DrawText(resultado.c_str(), 830, 625, 20, DARKGRAY);
        if (GetTime() - startTime < intervalo) {
            DrawText(resultado.c_str(), 830, 650, 30, RED);
        }
        EndDrawing();
    }
    UnloadTexture(image);
}

enum class CampoActivo3
{
    IndexBloque,
    Emisor,
    Receptor,
    Monto,
    fecha
};
void DrawInsert(blockchain& alfa,bool& shouldExit, bool& shouldMenu){
    char inputIndex[32] = {0};
    char inputEmisor[32] = {0};
    char inputReceptor[32] = {0};
    char inputMonto[32] = {0};
    char inputfecha[32] = {0};
    string resultado;
    CampoActivo3 campoActivo = CampoActivo3::IndexBloque;
    bool exitDraw = false;
    bool erroneo = false;
    double startTime = GetTime(); // Tiempo de inicio del mensaje
    double intervalo = 2.0; // Duración del mensaje en segundos
    Texture2D image = LoadTexture("../assets/KON_copi.png");  // Reemplaza "image.png" con el nombre de tu imagen
    while (!exitDraw)
    {
        DrawText("Blockchain", screenWidth / 2 - MeasureText("Blockchain", 200) / 2, 100, 200, WHITE);
        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);
        if (IsKeyPressed(KEY_ENTER))
        {
            std::string indexBloqueBuscado(inputIndex);
            std::string EmisorBuscar(inputEmisor);
            std::string ReceptorBuscar(inputReceptor);
            std::string MontoBuscar(inputMonto);
            std::string fechaBuscar(inputfecha);

            if (MontoBuscar.empty() || ReceptorBuscar.empty() || indexBloqueBuscado.empty() || EmisorBuscar.empty() || fechaBuscar.empty()){
                resultado = "Registro erroneo";
                startTime = GetTime(); // Reiniciar el tiempo de inicio cuando se muestra el mensaje
            }

            else{
                int bloqueindex = int(std::stod(indexBloqueBuscado));
                if (!alfa.isblock(bloqueindex)){
                    resultado = "Bloque no encontrado";
                    startTime = GetTime(); // Reiniciar el tiempo de inicio cuando se muestra el mensaje
                }
                else{
                    cout << "entrando a insertar" << endl;
                    double montoindex = std::stod(MontoBuscar);
                    cout << bloqueindex << endl;
                    size_t indice_barra_1 = fechaBuscar.find('/');
                    size_t indice_barra_2 = fechaBuscar.rfind('/');
                    std::string dia_str = fechaBuscar.substr(0, indice_barra_1);
                    std::string mes_str = fechaBuscar.substr(indice_barra_1 + 1, indice_barra_2 - indice_barra_1 - 1);
                    std::string anio_str = fechaBuscar.substr(indice_barra_2 + 1);
                    int dia = std::stoi(dia_str);
                    int mes = std::stoi(mes_str);
                    int anio = std::stoi(anio_str);
                    std::transform(EmisorBuscar.begin(), EmisorBuscar.end(), EmisorBuscar.begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                    std::transform(ReceptorBuscar.begin(), ReceptorBuscar.end(), ReceptorBuscar.begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                    cout << EmisorBuscar << endl;
                    cout << ReceptorBuscar << endl;
                    transaccion temp(montoindex,EmisorBuscar,ReceptorBuscar,dia,mes,anio);
                    alfa.insert_transaction(bloqueindex,temp);
//                exitDraw = true;
//                shouldMenu = true;
                }

            }
            memset(inputIndex, 0, sizeof(inputIndex));
            memset(inputEmisor, 0, sizeof(inputEmisor));
            memset(inputReceptor, 0, sizeof(inputReceptor));
            memset(inputMonto, 0, sizeof(inputMonto));
            memset(inputfecha, 0, sizeof(inputfecha));

        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            shouldMenu = true;
            exitDraw = true;
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            switch (campoActivo)
            {
                case CampoActivo3::IndexBloque:
                {
                    int lengthIndexBloque = strlen(inputIndex);
                    if (lengthIndexBloque > 0)
                        inputIndex[lengthIndexBloque - 1] = '\0';
                }
                    break;
                case CampoActivo3::Emisor:
                {
                    int lengthIndexTransaccion = strlen(inputEmisor);
                    if (lengthIndexTransaccion > 0)
                        inputEmisor[lengthIndexTransaccion - 1] = '\0';
                }
                    break;
                case CampoActivo3::Receptor:
                {
                    int lengthValor = strlen(inputReceptor);
                    if (lengthValor > 0)
                        inputReceptor[lengthValor - 1] = '\0';
                }
                    break;
                case CampoActivo3::Monto:
                {
                    int lengthCambio = strlen(inputMonto);
                    if (lengthCambio > 0)
                        inputMonto[lengthCambio - 1] = '\0';
                }
                    break;
                case CampoActivo3::fecha:
                {
                    int lengthCambio = strlen(inputfecha);
                    if (lengthCambio > 0)
                        inputfecha[lengthCambio - 1] = '\0';
                }
                    break;
            }
        }
        else
        {
            switch (campoActivo)
            {
                case CampoActivo3::IndexBloque:
                {
                    int lengthIndexBloque = strlen(inputIndex);
                    if (lengthIndexBloque < sizeof(inputIndex) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputIndex[lengthIndexBloque] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case CampoActivo3::Emisor:
                {
                    int lengthIndexTransaccion = strlen(inputEmisor);
                    if (lengthIndexTransaccion < sizeof(inputEmisor) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputEmisor[lengthIndexTransaccion] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case CampoActivo3::Receptor:
                {
                    int lengthValor = strlen(inputReceptor);
                    if (lengthValor < sizeof(inputReceptor) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputReceptor[lengthValor] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case CampoActivo3::Monto:
                {
                    int lengthCambio = strlen(inputMonto);
                    if (lengthCambio < sizeof(inputMonto) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputMonto[lengthCambio] = static_cast<char>(key);
                        }
                    }
                }
                    break;
                case CampoActivo3::fecha:
                {
                    int lengthCambio = strlen(inputfecha);
                    if (lengthCambio < sizeof(inputfecha) - 1)
                    {
                        int key = GetKeyPressed();
                        if ((key >= 32) && (key <= 125))
                        {
                            inputfecha[lengthCambio] = static_cast<char>(key);
                        }
                    }
                }
                    break;

            }
        }

        if (IsKeyPressed(KEY_UP))
        {
            switch (campoActivo)
            {
                case CampoActivo3::IndexBloque:
                    campoActivo = CampoActivo3::fecha;
                    break;
                case CampoActivo3::Emisor:
                    campoActivo = CampoActivo3::IndexBloque;
                    break;
                case CampoActivo3::Receptor:
                    campoActivo = CampoActivo3::Emisor;
                    break;
                case CampoActivo3::Monto:
                    campoActivo = CampoActivo3::Receptor;
                    break;
                case CampoActivo3::fecha:
                    campoActivo = CampoActivo3::Monto;
                    break;
            }
        }

        if (IsKeyPressed(KEY_DOWN))
        {
            switch (campoActivo)
            {
                case CampoActivo3::IndexBloque:
                    campoActivo = CampoActivo3::Emisor;
                    break;
                case CampoActivo3::Emisor:
                    campoActivo = CampoActivo3::Receptor;
                    break;
                case CampoActivo3::Receptor:
                    campoActivo = CampoActivo3::Monto;
                    break;
                case CampoActivo3::Monto:
                    campoActivo = CampoActivo3::fecha;
                    break;
                case CampoActivo3::fecha:
                    campoActivo = CampoActivo3::IndexBloque;
                    break;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Bloque ID:", 700, 460, 20, DARKGRAY);
        DrawRectangle(900, 460, 200, 30, campoActivo == CampoActivo3::IndexBloque ? SKYBLUE : LIGHTGRAY);
        DrawText(inputIndex, 930, 465, 20, GRAY);

        DrawText("Emisor:", 700, 500, 20, DARKGRAY);
        DrawRectangle(900, 500, 200, 30, campoActivo == CampoActivo3::Emisor ? SKYBLUE : LIGHTGRAY);
        DrawText(inputEmisor, 930, 505, 20, GRAY);

        DrawText("Receptor:    ", 700, 540, 20, DARKGRAY);
        DrawRectangle(900, 540, 200, 30, campoActivo == CampoActivo3::Receptor ? SKYBLUE : LIGHTGRAY);
        DrawText(inputReceptor, 930, 545, 20, GRAY);

        DrawText("Monto:", 700, 580, 20, DARKGRAY);
        DrawRectangle(900, 580, 200, 30, campoActivo == CampoActivo3::Monto ? SKYBLUE : LIGHTGRAY);
        DrawText(inputMonto, 930, 585, 20, GRAY);

        DrawText("Fecha:", 700, 620, 20, DARKGRAY);
        DrawRectangle(900, 620, 200, 30, campoActivo == CampoActivo3::fecha ? SKYBLUE : LIGHTGRAY);
        DrawText(inputfecha, 930, 625, 20, GRAY);
        if (IsKeyPressed(KEY_ESCAPE)){

        }
//        DrawText("Resultado:", 800, 620, 20, DARKGRAY);
//        DrawText(resultado.c_str(), 830, 625, 20, DARKGRAY);
        if (GetTime() - startTime < intervalo) {
            DrawText(resultado.c_str(), 830, 680, 30, RED);
        }
        EndDrawing();
    }
    UnloadTexture(image);
}


void DrawSearch(blockchain& alfa,bool& shouldExit, bool& shouldMenu) {

    const int fontSize = 24;
    const int menuOptionsCount = 4;

    bool enterKeyPressed = false;
    int selectedOption = 0;
    Texture2D image = LoadTexture("../assets/conan.png");  // Reemplaza "image.png" con el nombre de tu imagen
    const int menuOptionsCountH = 2;
    int selectedOptionH = 0;
    std::string options2[menuOptionsCountH] = {"Bloque", "Transacciones" };
    while (!enterKeyPressed) {
        cout << selectedOptionH << endl;
        if (IsKeyPressed(KEY_LEFT)) {
            selectedOptionH = (selectedOptionH - 1 + menuOptionsCountH) % menuOptionsCountH;
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            selectedOptionH = (selectedOptionH + 1) % menuOptionsCountH;
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + menuOptionsCount) % menuOptionsCount;
        }

        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % menuOptionsCount;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 0){
                DrawLoading2();
                if (selectedOptionH== 0){
                    drawOption1_index(alfa);
                }
                else{
                    drawOption1(alfa);
                }
            }
            else if (selectedOption == 1){
                DrawLoading2();
                if (selectedOptionH == 0){
                    drawOption2_index(true,alfa);
                }
                else{
                    drawOption2(true,alfa);
                }
            }
            else if (selectedOption == 2){
                DrawLoading2();
                if (selectedOptionH == 0){
                    drawOptions3_block(true,alfa);
                }
                else{
                    drawOptions4(true,alfa);
                }
            }
            else if (selectedOption == 3){
                DrawLoading2();
                if (selectedOptionH == 0){
                    drawOptions4_index(true,alfa);
                }
                else{
                    drawOptions4(true,alfa);
                }
            }
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            shouldMenu = true;
            enterKeyPressed = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);

        DrawText("Search Options:", screenWidth / 2 - MeasureText("Search Options:", fontSize) / 2, screenHeight / 2 - (menuOptionsCount + 1) * fontSize, fontSize, WHITE);

        std::string options[menuOptionsCount] = { "Search", "Range Search", "Start With", "Contains" };

        for (int i = 0; i < menuOptionsCount; i++) {
            if (i == selectedOption) {
                DrawText("->", screenWidth / 2 - MeasureText("->", fontSize) - 10, screenHeight / 2 - (menuOptionsCount - i) * fontSize, fontSize, GREEN);
                DrawText(options[i].c_str(), screenWidth / 2 + 10, screenHeight / 2 - (menuOptionsCount - i) * fontSize, fontSize, GREEN);
            }
            else {
                DrawText(options[i].c_str(), screenWidth / 2, screenHeight / 2 - (menuOptionsCount - i) * fontSize, fontSize, WHITE);
            }
        }
        if (selectedOptionH >= 0 && selectedOptionH < menuOptionsCountH) {
            DrawText("<", screenWidth / 2 - MeasureText(options2[selectedOptionH].c_str(), fontSize) - 100, 200, fontSize, GREEN);
            DrawText(options2[selectedOptionH].c_str(), screenWidth / 2 - MeasureText(options2[selectedOptionH].c_str(), fontSize) / 2, 200, fontSize, GREEN);
            DrawText(">", screenWidth / 2 + MeasureText(options2[selectedOptionH].c_str(), fontSize) + 100, 200, fontSize, GREEN);
        }
        EndDrawing();
    }
    UnloadTexture(image);

}


void DrawBlocks(bool visible, bool& shouldexit, bool& shouldMenu, blockchain& bchain) {
    if (!visible) {
        return;
    }
    Texture2D image = LoadTexture("../assets/bloque.png");  // Reemplaza "image.png" con el nombre de tu imagen
    Texture2D image2 = LoadTexture("../assets/bloque_alterado.png");  // Reemplaza "image.png" con el nombre de tu imagen

    Font customFont = LoadFont("../fonts/VCR_OSD_MONO.ttf");
    const int blockWidth = 800;
    const int blockHeight = 120;
    const int padding = 20;



    const int blocksPerRow = screenWidth / (blockWidth + padding);

    int startX = (screenWidth - (blocksPerRow * (blockWidth + padding) - padding)) / 2;
    int startY = padding;


    bool exitblock = false;
    while (!exitblock){
        BeginDrawing();
        ClearBackground(BLACK);
        int x = startX;
        int y = startY;

        // Dibuja los bloques
        for(int i = 1; i <= bchain.get_id();i++ ){
            auto block = bchain.find_block(i);
            if (block->valido){
                DrawTexture(image, x, y, WHITE);

//            DrawRectangle(x, y, blockWidth, blockHeight, GREEN);
            }
            else{
                DrawTexture(image2, x, y, WHITE);

//            DrawRectangle(x, y, blockWidth, blockHeight, RED);
            }
            string id_visual = "BLOQUE: " + to_string(block->id);
            string nonce = "nonce: " + to_string(block->nonce);
            string prevHash_visual = "prev_hash: " + block->prev_hash;
            string currentHash_visual = "current_hash: " + block->current_hash;
            DrawText(id_visual.c_str(), x + 350, y + 2, 20, WHITE);
            DrawText(nonce.c_str(), x + 10, y + 35, 20, WHITE);
            DrawTextEx(customFont, prevHash_visual.c_str(), { static_cast<float>(x + 10), static_cast<float>(y + 64) }, 15, 0, WHITE);
            DrawTextEx(customFont, currentHash_visual.c_str(), { static_cast<float>(x + 10), static_cast<float>(y + 94) }, 15, 0, WHITE);

            x += blockWidth + padding;

            if (x >= startX + blocksPerRow * (blockWidth + padding)) {
                x = startX;
                y += blockHeight + padding;
            }

        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            shouldexit = false;
            shouldMenu = true;
            exitblock = true;
        }

        EndDrawing();
    }

}
void Minando() {
    const int fontSize = 24;

    const int animationFrames = 10;  // Número de fotogramas de la animación
    const int frameDuration = 10;   // Duración de cada fotograma en milisegundos

    bool exitLoading = false;

    int currentFrame = 0;
    int dotCount = 0;
    const std::string loadingText = "Minando";

    while (!exitLoading) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(loadingText.c_str(), screenWidth / 2 - MeasureText(loadingText.c_str(), fontSize) / 2, screenHeight / 2, fontSize, WHITE);

        // Generar los puntos de la animación
        std::string dots = "";
        for (int i = 0; i < dotCount; ++i) {
            dots += ".";
        }

        DrawText(dots.c_str(), screenWidth / 2 + MeasureText(loadingText.c_str(), fontSize) / 2 + 10, screenHeight / 2, fontSize, WHITE);

        // Incrementar el contador de fotogramas
        currentFrame++;

        // Cambiar el número de puntos después de cada fotograma
        if (currentFrame % frameDuration == 0) {
            dotCount = (dotCount + 1) % 4;  // Cambia entre 0, 1, 2 y 3
        }

        EndDrawing();

        // Salir del bucle de carga después de que se complete la animación
        if (currentFrame / frameDuration >= animationFrames) {
            exitLoading = true;
        }

        // Esperar el tiempo de un fotograma
        ::_sleep(frameDuration);
    }
}
void DrawLoading() {

    const int fontSize = 24;

    bool exitLoading = false;

    while (!exitLoading) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Loading...", screenWidth / 2 - MeasureText("Loading...", fontSize) / 2, screenHeight / 2, fontSize, WHITE);

        // Aquí puedes realizar cualquier procesamiento adicional necesario mientras se muestra la animación de carga
        // Por ejemplo, cargar datos, realizar cálculos, etc.

        EndDrawing();

        // Salir del bucle de carga después de un tiempo determinado
        // Puedes ajustar el valor de Sleep para controlar la duración de la animación
        ::_sleep(1000);
        exitLoading = true;  // Salir del bucle de carga
    }
}
std::pair<int, bool> ShowMenu() {

    const int fontSize = 24;
    const int menuOptionsCount = 6;
    Texture2D image = LoadTexture("../assets/bitcoinChan.png");  // Reemplaza "image.png" con el nombre de tu imagen
    int backgroundPosY = 0;
    Texture2D backgroundTexture = LoadTexture("../assets/bitcoin_background2.png");
    float backgroundOpacity = 0.35f;  // Opacidad inicial del fondo

    int selectedOption = 0;
    bool enterKeyPressed = false;
    bool shouldExit = false;
    bool escapeKeyPressed = false;
    int previousBackgroundPosY = 0;

    while (!enterKeyPressed && !shouldExit && !escapeKeyPressed) {
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + menuOptionsCount) % menuOptionsCount;
        }

        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % menuOptionsCount;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            enterKeyPressed = true;
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            escapeKeyPressed = true;
        }

        if (selectedOption == menuOptionsCount - 1 && IsKeyPressed(KEY_ENTER)) {
            shouldExit = true;
        }
        backgroundPosY += 1;

// Reiniciar la posición Y cuando el fondo haya pasado por completo
        if (backgroundPosY >= backgroundTexture.height)
            backgroundPosY = 0;

        BeginDrawing();
        ClearBackground(BLACK);
        // Dibujar el fondo sin interrupciones si se está moviendo

        DrawTexture(backgroundTexture, 0, backgroundPosY, Fade(WHITE, backgroundOpacity));
        DrawTexture(backgroundTexture, 0, backgroundPosY - backgroundTexture.height, Fade(WHITE, backgroundOpacity));

        DrawTexture(image, 50, (screenHeight - image.height) / 2, WHITE);

        DrawText("Blockchain", screenWidth / 2 - MeasureText("Blockchain", 200) / 2, 100, 200, WHITE);

        DrawText("Options:", screenWidth / 2 - MeasureText("Menu:", fontSize) / 2, screenHeight / 2 - (menuOptionsCount + 1) * fontSize, fontSize, WHITE);

        std::string options[menuOptionsCount] = { "View", "Insert","Alter", "Search","Minar", "Exit" };

        for (int i = 0; i < menuOptionsCount; i++) {
            if (i == selectedOption) {
                DrawText("->", screenWidth / 2 - MeasureText("->", fontSize) - 10, screenHeight / 2 - (menuOptionsCount - i) * fontSize, fontSize, GREEN);
                DrawText(options[i].c_str(), screenWidth / 2 + 10, screenHeight / 2 - (menuOptionsCount - i) * fontSize, fontSize, GREEN);
            }
            else {
                DrawText(options[i].c_str(), screenWidth / 2, screenHeight / 2 - (menuOptionsCount - i) * fontSize, fontSize, WHITE);
            }

        }

        EndDrawing();
    }

    if (escapeKeyPressed) {
        selectedOption = -1;
    }
    UnloadTexture(image);  // Libera la textura de la imagen cargada
    cout <<"select options: "<< selectedOption << endl;
    return std::make_pair(selectedOption, shouldExit);
}
struct app{
    static void runApp(blockchain& alfa){
        InitWindow(screenWidth, screenHeight, "Blockchain Visualization");
        SetTargetFPS(60);
        bool showMenu = true;
        bool shouldExit = false;

        // Redimensionar la imagen a un tamaño más pequeño
        int temp = 0;
        while (!shouldExit) {

            if (showMenu) {
                std::pair<int, bool> menuResult = ShowMenu();
                if (menuResult.first == 0) {
                    temp = menuResult.first ;
                    showMenu = false;
                }
                if (menuResult.first == 1) {
                    temp = menuResult.first ;
                    showMenu = false;
                }
                if (menuResult.first == 2) {
                    temp = menuResult.first ;
                    showMenu = false;
                }
                if (menuResult.first == 3){
                    temp = menuResult.first ;
                    showMenu = false;
                }
                if (menuResult.first == 4){
                    temp = menuResult.first ;
                    showMenu = false;
                }
                if (menuResult.second) {
                    shouldExit = true;
                }
            }
            else {
                BeginDrawing();
                ClearBackground(BLACK);
                if (temp == 0){
                    DrawBlocks(true,shouldExit,showMenu,alfa);
                }
                if (temp == 1){
                    DrawInsert(alfa,shouldExit,showMenu);
                }
                if (temp == 2){
                    DrawLoading2();
                    int selectedOption = 0;
                    DrawAlterar(alfa,shouldExit,showMenu);
                }
                if (temp == 3) {
                    DrawLoading2();
                    DrawSearch(alfa,shouldExit,showMenu);
                }
                if (temp == 4){
                    Minando();
                    alfa.mine_invalid_blocks();
                    showMenu = true;
                }
                EndDrawing();
            }
        }

        CloseWindow();
    }
};


int main() {
    vector<transaccion> total;
    transaccion a(100,"jesus","chavez",20,10,2022);
    transaccion b(200,"chambilla","chavez",21,10,2022);
    transaccion c(300,"rodrigo","hermes",22,10,2022);
    transaccion  d(400,"miguel","chavez",23,10,2022);
    transaccion e(500,"pedro","chavez",24,10,2022);
    transaccion f(150,"benjamin","chavez",25,10,2022);
    transaccion g(700,"joaquin","chavez",26,10,2022);
    total.push_back(a);
    vector<transaccion> trans2{c};
    vector<transaccion> trans3{b,d};
    vector<transaccion> trans4{e,f};
    vector<transaccion> transM{c,d,e};

    blockchain alfa(total);
    alfa.insert_block_with_transaction(trans2);
    alfa.insert_block_with_transaction(trans3);
    alfa.insert_block_with_transaction(trans4);

    app::runApp(alfa);

    return 0;
}

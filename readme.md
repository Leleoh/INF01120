# 🎵 Peppertune
**INF01120 - Desenvolvimento de Software (UFRGS 2026/1)**
**Professor:** Marcelo Pimenta

---

## 📌 Sobre o Projeto
O **Peppertune** é um **Sintetizador e Sequenciador de Texto para Música (Text-to-MIDI)** desenvolvido inteiramente em `C++`. 

A ferramenta permite que usuários leigos componham músicas apenas digitando texto no teclado. O sistema interpreta um texto puramente alfanumérico, converte letras e símbolos em notas, silêncios, andamentos e timbres, e gera um áudio real sendo reproduzido diretamente nos alto-falantes ou exportado como arquivo `.mid`.

## 👥 Integrantes
- Leonel Ferraz
- Matheus Bello
- Pietro Cassara

---

## 🏗️ Arquitetura do Sistema
O projeto adota uma arquitetura fortemente baseada em Programação Orientada a Objetos, com módulos independentes:

- 🖥️ **Interface (Frontend):** Construída sobre o `ImGui` e instanciada pelo `SDL3`. Cuida do "Game Loop", renderizando a caixa de texto e os sliders de customização de Oitava, BPM e Volume inicial.
- 🎼 **TextInterpreter (O Maestro):** O cérebro que interliga o texto com a música. Ele separa os blocos de texto (onde cada quebra de linha gera uma nova faixa musical) e instancia o contexto para a interpretação.
- 🗣️ **Voice & MusicContext:** Módulos que processam a lógica de conversão. O `MusicContext` armazena o "estado" da música (qual instrumento está tocando, qual a oitava atual), enquanto a `Voice` varre caractere por caractere e emite eventos (`VoiceEvents`) como notas, pausas e modulações.
- 🎛️ **MidiGenerator:** Responsável pelo áudio em si. Usa classes do projeto `MidiFile` para compilar os eventos e gerar um arquivo temporário, e então recarrega tudo na memória com o `TinyMidiLoader (tml)` e sintetiza o áudio real-time com o `TinySoundFont (tsf)`, cuspindo o som através do subsystem de áudio do `SDL3`.

---

## 🎹 Como Usar / Sintaxe Musical
Após abrir o programa, digite sua composição na caixa de texto. O mapeamento é feito pela seguinte regra de caracteres:

* **Notas Musicais (Maiúsculas):** `A` até `H` (O caractere `H` equivale a um Si bemol / Bb).
* **Pausas (Minúsculas):** `a` até `h` geram silêncio na batida.
* **Oitavas:** Ponto `.` ou interrogação `?` sobem uma oitava. A letra `V` desce uma oitava.
* **Volume:** Um espaço em branco ` ` dobra o volume.
* **Instrumento:** Caracteres como exclamação `!` e vírgula `,`, bem como as vogais soltas `O, I, U` alteram o instrumento ativo (Órgão, Harpa, etc).
* **Andamento (BPM):** Os símbolos `<` e `>` diminuem ou aumentam a velocidade em 10 batidas por minuto.
* **Repetição:** Consoantes que não estão mapeadas repetem a última nota tocada.
* **Múltiplos Instrumentos:** Cada quebra de linha (`Enter`) cria um novo instrumento tocando ao mesmo tempo.

*(Exemplo Rápido: Para tocar a linha de baixo do **Seven Nation Army**, você pode digitar `EaEaGaEaDaCaaB`)*

---

## 🚀 Como Compilar e Rodar
O gerenciamento de pacotes e build é gerido pelo `CMake`.

### Pré-Requisitos
* Um compilador `C++` moderno (GCC, Clang ou MSVC)
* `CMake` instalado na máquina

### Passo a passo
1. Clone este repositório no seu computador.
2. Na raiz do repositório, rode os comandos:
   ```bash
   cmake -B build
   cmake --build build
   ```
3. ⚠️ **IMPORTANTE (O ÁUDIO):** Para que o programa toque o som corretamente, o arquivo SoundFont de instrumentos chamado `TimGM6mb.sf2` (disponível na raiz deste repositório) **deve** estar na mesma pasta do executável final gerado (ou seja, você precisará copiá-lo para dentro da pasta `build/Debug` ou rodar via linha de comando especificando o local correto).
4. Execute o binário `peppertune`.

---

## 🌿 Git Workflow (Para Contribuidores)
Utilizamos o **GitHub Flow** com foco em *Feature Branches*. **Nunca comite diretamente na branch `main` ou `develop`.**

### 1. Branches Principais
* **`main`**: Código de produção 100% testado.
* **`develop`**: Nossa branch de integração (o "ensaio geral").

### 2. Nomenclatura
Toda nova branch deve nascer a partir da `develop` seguindo as tags:
* `feat/`: Novas funcionalidades. *(Ex: feat/issue-2-setup)*
* `fix/`: Correção de bugs. *(Ex: fix/audio-estourando)*
* `docs/`: Arquivos de documentação. *(Ex: docs/att-diagrama)*
* `refactor/`: Refatorações e limpezas.

### 3. O Fluxo Diário
1. Vá para a branch: `git checkout develop`
2. Atualize o código: `git pull origin develop`
3. Crie a sua branch: `git checkout -b tipo/nome-da-branch`
4. Crie seus commits, dê o `push`, e abra um **Pull Request (Merge)** para a `develop`.
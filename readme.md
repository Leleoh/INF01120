# INF01120 - Desenvolvimento de Software
## PEPPERTUNE


## 📌 Descrição
Esse repositório contém os arquivos do projeto desenvolvido na disciplina de Desenvolvimento de Software no Instituto de Informática da UFRGS, ministrada pelo professor Marcelo Pimenta em 2026/1.
O objetivo é desenvolver a prática de programação modular com orientação a objetos.
A linguagem escolhida para desenvolver o projeto foi C++.

## 👥 Integrantes
- Leonel Ferraz
- Matheus Bello
- Pietro Cassara

## Git Workflow
Para manter o código organizado, evitar conflitos de merge e rastrear funcionalidades entregues, será usado o **GitHub Flow** com foco em *Feature Branches* 
**NUNCA comite diretamente na `main` ou na `develop`.**

### 1. Nossas Branches Principais
* **`main`**: Código de produção. Só recebe código testado, aprovado e funcional.
* **`develop`**: Nossa branch de integração. É o "ensaio geral" onde juntamos as partes de todo mundo antes de mandar para a `main`.

### 2. Padrão de Nomenclatura (Nomes das Branches)
Toda nova branch deve ser criada a partir da `develop` e deve ter um prefixo indicando o que está sendo feito.

* **`feat/`** (Feature): Para desenvolvimento de novas funcionalidades.
  * *Ex: `feat/issue-2-setup-inicial`*
* **`fix/`** (Bugfix): Para correção de bugs em funcionalidades já existentes.
  * *Ex: `fix/audio-estourando`*
* **`docs/`** (Documentação): Para alterações no README, PDFs, croquis, etc.
  * *Ex: `docs/att-diagrama-classes`*
* **`refactor/`**: Para refatoração de código (melhorar o código sem adicionar funcionalidade nova).

### 3. Fluxo para criar uma nova branch
1. Vá para a branch `develop`:
   ```bash
   git checkout develop
   ```
2. Atualize sua branch local com as últimas mudanças do repositório:
   ```bash
   git pull origin develop
   ```
3. Crie e mude para a sua nova branch (lembre-se de seguir o padrão de nomenclatura):
   ```bash
   git checkout -b tipo/nome-da-sua-branch
   ```

**Importante:** Todas as suas alterações devem ser integradas de volta à `develop` através de um **Merge (Pull Request)** a partir dessa sua branch. Nunca faça commits diretos na `develop`.
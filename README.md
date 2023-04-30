# Desafio Pixeon - Analista Desenvolvedor C++ Júnior

## Introdução

Este relatório visa explicar o algoritmo desenvolvido em C++ na plataforma QtCreator como desafio a vaga de Analista Desenvolvedor C++ Júnior na empresa Pixeon desenvolvido por Igor henrique Silva Barbosa.

## Métodologia 

Inicialmente foi criado um projeto do tipo "Qt Widgets Application" que permite a criação de uma aplicação baseada em uma interface gráfica. Dessa forma, o projeto conta com 4 arquivos principais, mainwindow.h, mainwindow.cpp, mainwindow.ui e main.cpp. Abaixo temos uma breve explicação de cada um desses arquivos.
 - **mainwindow.h:**  Declara todas as funções e váriaveis da classe MainWindow, assim como realiza a importação de todas as bibliotecas necessárias;
 - **mainwindow.cpp:** Define o comportamento de cada função e, consequentemente, o comportamento do aplicação;
 - **mainwindow.ui** Define a interface gráfica da aplicação, assim como os elementos que a compoem;
 - **main.cpp** Instância o objeto da aplicação.

### Estratégias Utilizadas

Todas as técnicas utilizadas são advindas de funções e bibliotecas nativas do próprio Qt. Nesse sentido, a interface gráfica foi constituída de vários QLabel's para expressar textos; um QLabel especifico para visualizar a imagem; um QPushButton para adicionar as imagens; um  QComboBox para selecionar a imagem a ser visualizada; cinco QSlider's para representar as funcionalidades de zoom, pan (x e y), brilho e rotação; um QPushButton para resetar os parâmetros dos slider's.
Nesse contexto, podemos segmentar a explicação do funcionamento da aplicação nos seguintes tópicos: Inicialização dos componentes, Adição e seleção de imagens, Visualização de imagens, Modificação dos parâmetros da imagem e Resete de parâmetros.

#### Inicialização dos componentes

Visando centralizar as configurações iniciais dos componentes da interface gráfica e as variáveis da classe MainWindow, foi criado a função **InitComponents**. Essa função define o valor inicial de variável do sistema, como zoom, pan e brilho, por exemplo. Assim como a configuração dos elementos gráficos da aplicação, por exemplo, os limites dos QSlider's (valor inicial e valor final) e o alinhamento e estilo de textos de QLabel's. 

#### Adição e seleção de imagens
Essa funcionalidade é acionada pelo disparo do evento de Clicked do botão de Adicionar imagens.  Esse evento inicialmente instancia um objeto da classe QFileDialog configurado para aceitar apenas arquivos existentes com as extensões .jpg e .jpeg. Ná prática essas duas extensões são equivalentes, entretanto, o QFileDialog realiza a diferenciação das mesmas, portanto, ambas foram adicionadas. O QFileDialog dispara a abertura de um modal de seleção de arquivos que limilitará a seleção aos formatos configurados e permite seleção múltipla. Sendo assim, o QFileDialog retorna uma lista de strings com o endereço de cada imagem selecionada, essa lista é salva em um atributo da classe MainWindow chamada filesNames de forma exclusiva, isto é, se o caminho de uma imagem já estiver nessa lista ela não pode ser adicionada novamente. Por fim, essa funcionalidade pode ser chamada a qualquer momento da execução da aplicação, passando o número de imagens desejado.
A seleção da imagem da lista a ser visualizada é feita através do evento de valueChange do QComboBox, esse contém todas os dados da lista caminhos de imagens, dessa forma, cada caminho é uma opção do QComboBox. Sendo assim, esse evento associa o index atual do QComboBox a uma váriavel da classe  MainWindow que tem como objetivo salvar o index da iamgem que deve ser carregada.

#### Visualização de imagens
Essa funcionalidade foi centralizada em uma única função da classe MainWindow intitulada de UpdateScreen. Essa função,  em primeiro lugar tenta carregar a imagem do index selecionado em um QPixmap que representa uma alternativa para manipulação de imagens com Qt. Caso esse load apresente sucesso, é iniciado a verificação dos parâmetros extra da visualização da imagem e são realizadas as seguintes operações de forma sequencial. 
 - **Zoom**: Nessa operação o QPixmap sofre uma modificação de escala no seu tamanho de acordo com o fator de zoom contida em uma váriavel da classe MainWindow. 
 - **Rotação** Nessa operação é utilizado um QPainter que é outro elemento do Qt que permite a alteração do Qpixmap com funções de translação e rotação. Sendo assim, em primeiro lugar é criado um QPixmap auxiliar com valores vazios para servir como receptáculo do resultado da operação, em seguida ele é transladado, rotacionado de acordo com uma váriavel da classe MainWindow que representa o angulo de rotação, é transladado novamente, isso é feito visando evitar que a imagem seja descentralizada na rotação, por isso existe uma translação antes e outra depois da rotação corrigindo a anterior. Dessa forma é gerado um novo QPixmap rotacionado de acordo com o angulo que é salvo no QPixmap original.
 - **Pan (X , Y)** Essa operação também utiliza um QPainter, e também realiza a criação de um QPixmap auxiliar para a operação. Dessa forma, o QPixmap resultante nada mais é do que o original transladado em X e Y de acordo com duas váriaveis da classe MainWindow. E assim, como nas operações anteriores o QPixmap resultante é salvo no original.
 - **Brilho** Essa operação funciona da mesma forma que as últimas duas com QPainter, realizando apenas a alteração da opacidade da imagem de acordo com uma váriavel da MainWindow. E o resultado também é salvo no QPixmap original.

Dessa forma, ao final das operações temos a aplicação de todos os parâmetros na imagem original e por fim esse QPixmap é atribuído ao QLabel responsável pela visualização da imagem. 

#### Modificação dos parâmetros das imagens
Essa funcionalidade é distribuída nos eventos de valueChange de todos os QSlider's de parâmetros. Sendo assim, sempre que um deles é modificado, o respectivo evento é chamado alterando a respectiva variável da classe MainWindow e no final esse evento invoca a função UpdateScreen. Por exemplo, ao alterar o valor do slider de zoom a variavel de zoom será atualizada e o UpdateScreen que lê essa váriavel será chamado e atualizará a visualização conforme esse novo valor de zoom. O mesmo acontece para os demais parâmetros.

#### Resete de parâmetros 
Essa funcionalidade é atribuída ao evento de Clicked do botão de resete que invoca uma função da MainWindow que volta todas as váriaveis de paramêtro para seus estados iniciais e também modifica o posicionamento dos sliders de acordo com esses valores.

## Dificuldades encontradas

Dentre as dificuldades encontradas a principal foi a funcionalidade de rotação que demandou um tempo maior de pesquisa e entendimento. Embora o seu desenvolvimento seja parecido com o Pan, o seu comportamento pode mudar completamente a estrutura do QPixmap. Outro ponto a se citar é que as operações de modificação de visualização de imagens foram feitas de forma sequêncial e separadas visando facilitar o entendimento e segmentação de possíveis problemas. Entretanto, essa ordem se torna restrita a realizar sempre o deslocamento primeiro, uma vez que o deslocamento (Pan) modifica o centro do pixmap que ao ser rotacionado pode ocasionar em bugs de visualização. Esse problema foi amenizado, mas ainda ocorre caso seja feito a rotação de um pixmap deslocado, em algumas ocasiões bordas da imagem são cortadas. Dessa forma, a possibilidade de poder realizar todas as modificações de parâmetros ao mesmo tempo em uma mesma imagem foi um pouco complexo de entender e certamente existe espaço para melhorias. 

## Melhorias futuras

De acordo com a seção anterior, o principal ponto a ser tratado é a funcionalidade de rotação, que embora funcione, em alguns cenários especificos pode apresentar erros quando usadas em conjunto com os deslocamento. O design gráfico também apresenta espaço para melhorias uma vez que o foco maior foram as funcionalidades.

## Conclusão

De forma geral, foi possível perceber que a aplicação possui espaço para futuros aperfeiçoamentos ou até mesmo a inclusão de novas funcionalidades, um exemplo a ser citado é a funcionalidade extra de rotação. Contudo, foi possível atingir o objetivo proposto, uma vez que é possível selecionar e visualizar várias imagens do formato JPG em uma aplicação C++ utilizando uma interface gráfica construída com Qt. Outro ponto a se destacar é que particularmente nunca tinha usado a visualização de imagens antes com QPixmap e Qlabel, apenas com outros frameworks mais específicos para esse tipo de aplicação, como o openCV, por exemplo. Sendo assim, foi possível desenvolver e conhecer técnologias novas.

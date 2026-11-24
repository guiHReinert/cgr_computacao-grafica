# Material de Construção de Objetos

Disponível nos slides do TC1.

## Construindo (modelando) Objetos

- Em OpenGL é possível modelar combinando objetos pré-definidos.
- Formas quádricas.
- Objetos complexos requerem maior complexidade matemática. OpenGL dá suporte a geração de curvas e superfícies Bézier e NURBS que veremos mais adiante.

## Quádricas

- Diversos objetos podem ser modelados apenas com o uso de formas quádricas.
- Para tanto, basta combiná-las para compor objetos mais complexos, como:
  - Visualização de moléculas em 3D (combinando esferas e cilindros)
  - Diversos objetos utilizados em jogos, como por exemplos, armas, veículos, projéteis, edificações e etc.

## Quádricas no OpenGL

Semelhante ao modelo OO, mantendo um estado do objeto "quádrico" na memória:

1. Criar um objeto que representa o estado da quádrica deve ser mantido para definir propriedades das quádricas.
2. Definir propriedades para o objeto
3. Desenhar a forma específica

```c
GLUquadricObj *pObj;
pObj = gluNewQuadric();
// ... Definições (estados)
gluDeleteQuadric(pObj);
```

Funções para definição de estados:

- Estilo de desenho:

```c
gluQuadricDrawStyle(GLUquadricObj *obj,
GLenum drawStyle)
- GLU_FILL, GLU_LINE, GLU_POINT e
GLU_SILHOUETTE
```

- Normais da superfície:

```c
gluQuadricNormals(GLUquadricObj *obj, GLenum
normals)
- GLU_NONE, GLU_FLAT // normais dos vértices perpendiculares as faces
  e GLU_SMOOTH // pondera normais com as das faces adjacentes
```

Funções para definição de estados:

- Orientação das normais:

```c
gluQuadricOrietantion(GLUquadricObj *obj,
GLenum orientation)
- GLU_OUTSIDE e GLU_INSIDE
```

- Considerar textura ou não:

```c
gluQuadricTexture(GLUquadricObj *obj, GLenum
texture)
- GL_TRUE // considera mapeamento de texturas
  e GLU_FALSE //não considera o mapeamento de textura
```

## Desenhando Quádricas

### Esferas

```c
gluSphere(GLUquadricObj *obj, GLdouble
radius, GLint slices, GLint stacks)
Slices // == gomos
Stacks // == rodelas
```

### Cilindros

```c
gluCylinder(GLUquadricObj *obj, GLdouble
baseRadius, GLdouble topRadius, GLdouble
height, GLint slices, GLint stacks)
topRadius // == zero, permite criar cone.
```

### Discos

```c
gluDisk(GLUquadricObj *obj, GLdouble
innerRadius, GLdouble outerRadius, GLint
slices, GLint loops)
innerRadius // != zero, permite criar discos com furos.
```

### Variável de Classe (declaração)

```c
GLUquadriObj *obj;
```

- init:

```c
obj = gluNewQuadric();
```

- RenderScene (ou display):

```c
gluQuadricNormals(obj, GLU_SMOOTH);
glTranslatef(x,y,z);
gluSphere(obj, 5, 5, 5);
```

- No final da execução:

```c
gluDeleteQuadric (obj);
```

## Modelagem com Quádricas

Vantagem:

- Facilidade de modelagem (criação, propriedades,
composição e desenho)

Desvantagens:

- Limitação de interação com o usuário
- Pode-se tornar difícil a criação de um cenário
grande.
- Limitação de formas matemáticas

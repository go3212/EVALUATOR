# EVALUATOR
1. nuevo_problema p: añade un problema nuevo con identificador p. El comando
admite la forma abreviada np p. Si ya existía un problema en la plataforma con el
mismo identificador se imprime un mensaje de error. En caso contrario se imprime
el número de problemas P en la colección después de añadirlo.
2. nueva_sesion s: añade una sesión nueva con identificador s. El comando admite la forma abreviada ns s. Primero se debe leer la estructura de problemas de la
sesión, de la misma manera que se hizo en las sesiones iniciales (se garantiza que
los problemas existen y no están repetidos). Si ya existía una sesión en la plataforma con el mismo identificador se imprime un mensaje de error. En caso contrario
se imprime el número de sesiones Q en el repositorio después de añadirla. Se garantiza que la nueva sesión no es igual a las ya existentes.
3. nuevo_curso: añade un nuevo curso con identificador N +1 en caso de que cumpla la restricción de no repetición de problemas en el mismo curso. El comando
admite la forma abreviada nc. Primero se lee un número de sesiones SN+1 > 0 y
luego una secuencia de SN+1 identificadores válidos de sesiones. Si no hay intersección de problemas entre las sesiones, se añade el curso al conjunto de cursos y
se imprime su identificador. En caso contrario, no se añade al conjunto (por lo que
N no varía) y se imprime un mensaje de error. Se garantiza que el nuevo curso no
es igual a los ya existentes.
4. alta_usuario u: registra un usuario nuevo con identificador u. El comando admite la forma abreviada a u. Si ya existía un usuario en la plataforma con el mismo identificador se imprime un mensaje de error. En caso contrario se imprime el
número de usuarios registrados M después de añadirlo.
5. baja_usuario u: da de baja un usuario con identificador u. El comando admite
la forma abreviada b u. Si no existe un usuario en la plataforma con identificador
u se imprime un mensaje de error. En caso contrario se imprime el número de
usuarios registrados M después de borrarlo. Si más tarde se da de alta otro usuario
con el mismo nombre es como si el anterior no hubiera existido.
6. inscribir_curso u c: inscribe un usuario u en el curso con identificador c. El
comando admite la forma abreviada i u c. Si el usuario u o el curso c no existen
en la plataforma o u ya está inscrito en otro curso que no ha sido completado, se
imprime un mensaje de error. En caso contrario se imprime el número de usuarios
inscritos en el curso c después de añadirlo (se garantiza que el usuario u no se ha
inscrito con anterioridad al curso c).
©PRO2, CS-UPC 47. curso_usuario u: consulta el curso en el que está inscrito un usuario u. El comando admite la forma abreviada cu u. Si el usuario u no existe en la plataforma
se imprime un mensaje de error. En caso contrario, se imprime el identificador del
curso o un cero si no está inscrito en ningún curso.
8. sesion_problema c p: consulta la sesión del problema p en el curso con identificador c. El comando admite la forma abreviada sp c p. Si el curso c no existe o
si el problema p no existe o si el problema p no pertenece al curso c, se imprime un
mensaje de error. En caso contrario, se imprime el identificador de la sesión donde
se realiza el problema p en el curso c.
9. problemas_resueltos u: se listan en orden creciente por identificador los problemas solucionados con éxito por el usuario u, ya sea en el curso en que está
inscrito actualmente (si lo está en alguno) como los resueltos en cursos anteriores.
Además de los identificadores se imprime también el número de envíos realizados por el usuario a cada problema del listado (valor mayor o igual que uno). Si el
usuario u no existe en la plataforma, se imprime un mensaje de error. El comando
admite la forma abreviada pr u.
10. problemas_enviables u: se listan en orden creciente por identificador los problemas que el usuario no ha solucionado todavía en el curso en el que está inscrito
actualmente, pero a los cuales ya puede realizar un envío (porque cumple todos
sus prerrequisitos, directos e indirectos). Además de los identificadores se imprime también el número de envíos realizados por el usuario a cada problema del
listado (valor mayor o igual que cero). Si el usuario u no existe en la plataforma
o no está inscrito en ningún curso, se imprime un mensaje de error. El comando
admite la forma abreviada pe u.
11. envio u p r: se toma nota del resultado r (r = 1 si éxito o r = 0 si fallo) de
un nuevo envío del usuario u al problema p. Se garantiza que el usuario u está
registrado e inscrito en un curso donde aparece el problema p y que p pertenece
al conjunto de problemas a los que u puede enviar una solución por cumplir los
prerrequisitos. Todo envío da lugar a la actualización de las estadísticas del usuario
y del problema. Además, en el caso r = 1 también hay que actualizar los problemas
resueltos y enviables del usuario y comprobar si con ello ha completado el curso en
el que estaba inscrito. En caso de que lo haya completado, el usuario deja de estar
inscrito en el curso. El problema p se considera resuelto (y, por tanto, no podrá ser
enviable) por parte de u en todo otro curso en el que u se inscriba más adelante †
.
El comando admite la forma abreviada e u p r.
12. listar_problemas: se listan los problemas de la colección, indicando para cada
problema el número t de envíos totales y el número e de envíos con éxito a dicho
problema, en ambos casos de usuarios presentes o pasados. También se ha de escribir el ratio (t + 1)/(e + 1), y los problemas han de listarse en orden creciente
†No obstante, si en uno de esos otros cursos el problema p tiene como prerrequisitos problemas que
el usuario u no ha resuelto, entonces el usuario u deberá resolver todos ellos para poder completar el
curso y, de hecho, los deberá resolver antes que cualquier otro problema no resuelto que tenga a p como
prerrequisito en ese curso.
5 ©PRO2, CS-UPCpor dicho ratio. En caso de empate, se han de listar por orden creciente de identificador. El comando admite la forma abreviada lp. Si se desea lo mismo para un
solo problema se usa escribir_problema p. Si p no existe en la plataforma se
imprime un mensaje de error. El comando admite la forma abreviada ep p.
13. listar_sesiones: se listan las sesiones actuales de la plataforma, ordenadas
crecientemente por su identificador y mostrando, para cada sesión, el número de
problemas que la forman y los identificadores de dichos problemas, siguiendo su
estructura de prerrequisitos en postorden. El comando admite la forma abreviada
ls. Si se desea lo mismo para una sola sesión se usa escribir_sesion s. Si s
no existe en la plataforma se imprime un mensaje de error. El comando admite la
forma abreviada es s.
14. listar_cursos: se listan los cursos actuales de la plataforma, ordenados crecientemente por su identificador y mostrando, para cada curso, el número de usuarios
actuales o pasados que lo han completado, el número de usuarios inscritos actualmente, el número de sesiones que lo forman y los identificadores de dichas
sesiones, en el mismo orden en el que se leyeron cuando se creó el curso. El comando admite la forma abreviada lc. Si se desea lo mismo para un solo curso se
usa escribir_curso c. Si c no existe en la plataforma se imprime un mensaje
de error. El comando admite la forma abreviada ec c.
15. listar_usuarios: se listan los usuarios registrados actualmente en la plataforma, ordenados crecientemente por su nombre y mostrando, para cada usuario,
cuántos envíos en total ha realizado, cuántos problemas ha resuelto satisfactoriamente, cuántos problemas ha intentado resolver (al menos ha hecho un envío), y
el identificador del curso en el que está inscrito o un cero si no está inscrito en
ninguno. El comando admite la forma abreviada lu. Si se desea lo mismo para
un solo usuario se usa escribir_usuario u. Si u no existe en la plataforma se
imprime un mensaje de error. El comando admite la forma abreviada eu u.
16. fin: termina la ejecución del programa

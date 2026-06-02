# Укажите SGDK путь
GDK := C:/sgdk

# Переопределяем уровень оптимизации
CFLAGS = -O1

# Подключаем стандартный makefile SGDK
include $(GDK)/makefile.gen
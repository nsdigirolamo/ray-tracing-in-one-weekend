CC = gcc
SDIR = srcs
IDIR = headers
ODIR = objs

OBJS += $(ODIR)/ray-tracer.o
OBJS += $(ODIR)/vector3.o
OBJS += $(ODIR)/point3.o
OBJS += $(ODIR)/color.o
OBJS += $(ODIR)/ray.o
OBJS += $(ODIR)/sphere.o
OBJS += $(ODIR)/hit.o
OBJS += $(ODIR)/camera.o
OBJS += $(ODIR)/random_utils.o
OBJS += $(ODIR)/material.o

CFLAGS = -I $(IDIR)
LIBS = -lm

ray-tracer: $(OBJS)
	$(CC) -o ray-tracer $(OBJS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR): mkdir -p $@ 

.PHONY: clean

clean:
	rm $(ODIR)/*.o ray-tracer
create table equipos(
    codE varchar2(3) constraint codE_pk primary key,
    nombreE varchar2(20) constraint nombreE_nn not null constraint nombreE_u unique,
    localidad varchar2(10) constraint localidad_nn not null,
    entrenador varchar2(20) constraint entrenador_nn not null,
    fecha_crea date constraint fecha_crea_nn not null);
    
create table jugadores(
    codJ VARCHAR2(3) constraint codJ_pk primary key,
    codE varchar2(20) constraint codE_ek references equipos(codE),
    nombreJ varchar2(20) constraint nombreJ_nn not null);

create table encuentros(
    Elocal constraint Elocal_ek references equipos(codE),
    Evisitante constraint Evisitante_ek references equipos(codE),
    fecha date,
    PLocal number default Plocal=0 constraint Plocal_nn not null,
    PVisitante number default 0 constraint PVisitante_nn not null,
    constraint encuentros_pk primary key (Elocal,Evisitante));
    
create table faltas(
    codJ constraint codJ_ek references jugadores(codJ),
    Elocal constraint Elocal_ek references encuentros(Elocal),
    Evisitante constraint Evisitante_ek references encuentros(Evisitante),
    numfaltas number default 0 constraint numfaltas_b0y5 check(numfaltas between 0 and 5),
    constraint faltas_pk primary key (codJ,Elocal,Evisitante));
    
commit;

C234567
C A FINITE ELEMENT CODE FOR SOLVING PLANE ELASTICITY
C PISS=1 SOLVES PLANE STRAIN PROBLEM
C PISS NON EQUAL TO 1 SOLVES THE PLANE STRESS PROBLEM

C234567
      PROGRAM PROJECT2
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION IELMN(800,3),SLM(6,6),GSM(902,24),KK(6),CORD(451,2),
     *B(3,6),B1(3,6),BT(6,3),D(3,3),IGG(22),F(902),STRAIN(3,1),
     *UEL(6),STRESS(3,1)



C     ELASTIC CONSTANTS EY=YOUNG MODULUS, V=POISSON'S RATIO, D=ELASIC MATRIX

      PISS=11.0
      IF(PISS.EQ.1)GO TO 6
      WRITE(6,99)
      WIDTH=1.0
      GO TO 7
 6    WRITE(6,98)
      WIDTH=1.0
 7    EY=210000
      V=0.25
      CALL ELASTI (EY,V,PISS,D)
      WRITE(6,100) ((D(I,J),J=1,3),I=1,3)

C     DADA----GEOMETRY OF THE BODY
C     XL------LENGTH OF THE BODY
C     YL------HEIGHT OF THE BODY
C     NGP-----# OF GRID POINTS:::NEL=# OF ELEMENTS
C     IBAND-----BANDWIDTH
C     H-----DISPLACEMENT BOUNDARY LENGTH
C     QP-----APPLIED TRACTION IN THE Y-DIRECTION
C
C
C      PI=DATAN(1.0D0)*4.0D0
C
C
C234567
      XL=10.0
      YL=1.0
      H=YL
      QP=-10.0
      N=40
      M=10

      DX=XL/N
      DY=YL/M
      XII=0.25
      N1=N+1
      M1=M+1
      M22=M1*2
      NGP=N1*M1
      NGP2=NGP*2
      IBAND=(M1+1)*2
      NEL=M*N*2

C MATRIX DESCRIPTION
C CORD(NGP,2)----COORDINATE'S MATRIX
C IELMN(NEL,3)----ASSOCIATES EACH ELEMENT WITH ITS NODES
C B1=D*B(3,6)
C BT(6,3)----TRANSPOSE OF B1
C SLM(6,6)----ELEMENT STIFFNESS MATRIX IN GLOBAL SENSE
C GSM(NGP2,IBAND)----GLOBAL STIFFNESS MATRIX
C F(NGP2)-----GLOBAL FORCE VECTOR

C234567
      DO 8 I=1,NGP2
      DO 8 J=1,IBAND
 8    GSM(I,J)=0.0
      CALL CRDIXY(M1,N1,NGP,DX,DY,CORD)
      CALL INODES(M,N,M1,NEL,IELMN)

      DO 40 L=1,NEL
      CALL BETA (L,CORD,IELMN,NGP,NEL,DA,B)
      CALL MULT (D,B,B1,3,3,6)
      DO 41 I=1,3
      DO 41 J=1,6
 41   BT(J,I)=B(I,J)
      CALL MULT(BT,B1,SLM,3,6,6)
      DO 42 IS=1,6
      DO 42 JS=1,6
 42   SLM(IS,JS)=SLM(IS,JS)*DA*WIDTH/2.0
      CALL ASSEMB(IELMN,SLM,NEL,NGP2,IBAND,L,GSM)
 40   CONTINUE

C APPLY GEOMETRIC BCS

      DO 50 I=1,NGP2
 50   F(I)=0.0
      NGP3=NGP-M1
      DO 60 I=M1,NGP3,M1
      F(2*I-1)=F(2*I-1)+0.0
      F(2*I)=F(2*I)+QP*XII/2.0
      F(2*(I+M1)-1)=F(2*(I+M1)-1)+0.0
 60   F(2*(I+M1))=F(2*(I+M1))+QP*XII/2.0
      DO 70 I=1,M1
      SOF=(I-1)*DY+H
      IF(SOF.LT.YL) GO TO 70
      IGG(2*I-1)=2*I-1
      IGG(2*I)=2*I
 70   CONTINUE
      WRITE(6,101)
      WRITE(6,102)(I,I=1,M1)
      WRITE(6,103)
      WRITE(6,104)
      DO 80 KX=1,4
      WRITE(6,105)(((I-1)*M1+11),I=((KX-1)*10+1),KX*10)
 80   WRITE(6,106)(F(((I-1)*M1+11)*2),I=((KX-1)*10+1),KX*10)
      I=451
      WRITE(6,107) I,F(I*2)

      CALL BOUNDA (M22,NGP2,IBAND,IGG,GSM,F)

C SOLVE FOR NODAL DISPLACEMENTS

      CALL HALLEY (1,GSM,F,NGP2,IBAND)
      CALL HALLEY (2,GSM,F,NGP2,IBAND)
      WRITE(6,111)
      WRITE(6,112)(I,F(2*I-1),F(2*I),I=1,NGP)

C CALCULATION OF THE STRESS FIELD STRESS=STRAIN *D

      WRITE(6,113)
      DO 200 I=1,NEL
      DO 199 J=1,3
      JPN=IELMN(I,J)
      UEL(2*J-1)=F(2*JPN-1)
 199  UEL(2*J)=F(2*JPN)

      CALL BETA (I,CORD,IELMN,NGP,NEL,DA,B)
      CALL MULT (B,UEL,STRAIN,6,3,1)
      CALL MULT (D,STRAIN,STRESS,3,3,1)

      WRITE(6,114)I,(STRESS(IT,1),IT=1,3)
 200  CONTINUE
      WRITE(6,115)

 98   FORMAT(//,10X,'PLAIN STRAIN CASE')

 99   FORMAT(//,10X,'PLAIN STRESS CASE')

 100  FORMAT(//,10X,'ELASTIC MATRIX D',/(35X,3(F10.2,2X)))

 101  FORMAT(5(/),10X,'DISPLACEMENT BOUNDARY CONDITIONS')

 102  FORMAT(//,4X,'NODE',11(4X,I2,4X))

 103  FORMAT(/,10X,11(2X,'UX=0.0',2X)/10X,11(2X,'UY=0.0',2X))

 104  FORMAT(5(/),10X,'TRACTION BC')

 105  FORMAT(//,4X,'NODE',10(4X,I3,4X))

 106  FORMAT(/,10X,10(2X,'FX=0.0',3X)/10X,10(2X,'FY=',F5.2,1X))

 107  FORMAT(//,4X,'NODE',4X,I3,//,12X,'FX=0.0'/12X,'FY=',F5.2)

 111  FORMAT(///,47X,'D',2X,'I',2X,'S',2X,'P',2X,'L',2X,'A',2X,'C',

     *2X,'E',2X,'M',2X,'E',2X,'N',2X,'T',2X,'S',/,40X,50('.'),5(/),

     :28X,76('*'),/,28X,2('*',6X,'*',2(14X,'*')),/,28X,2('*',1X,'NODE',

     *1X,'*',6X,'UX',6X,'*',6X,'UY',

     *6X,'*'),/,28X,2('*',6X,'*',2(14X,'*')),/,28X,76('*'))

 112  FORMAT((28X,2('*',1X,I4,1X,'*',2(1X,F12.8,1X,'*'))))

 113  FORMAT(28X,76('*'),6(/),55X,'S',2X,'T',2X,'R',2X,'E',2X,'S',2X,
     *'S',2X,'E',2X,'S',/,50X,32('.'),5(/),35X,61('*'),/,35X,'*',4(14X,
     *'*'),/,35X,'*',
     *4X,'ELEMENT',3X,'*',6X,'SX',6X,'*',6X,'SY',6X,'*',6X,'SXY',5X,'*',
     */,35X,'*',4(14X,'*'),/,35X,61('*'))

 114  FORMAT((35X,'*',5X,I4,5X,'*',3(1X,F12.4,1X,'*')))
 115  FORMAT(35X,61('*'))

      STOP
      END
C
C*****************************************************
C
      SUBROUTINE CRDIXY(M1,N1,NGP,DX,DY,CORD)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION CORD(NGP,2)
C
      DO 1 I=1,M1
      DO 1 J=1,N1

         JP=(J-1)*M1+I
         CORD(JP,1)=(J-1)*DX
         CORD(JP,2)=(I-1)*DY
 1       CONTINUE
C
C
      WRITE(6,100)(I,(CORD(I,J),J=1,2),I=1,NGP)
 100  FORMAT("COORDINATE MATRIX",/,((I5,2X,F12.5,F12.5)))
C
C
      RETURN
      END
C
C*****************************************************
C
      SUBROUTINE INODES(M,N,M1,NEL,IELMN)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION IELMN(NEL,3)
C
C
      DO 10 J=1,N
      LP=(J-1)*M1
      KP=LP+1
      DO 10 I=1,M
      KK1=(J-1)*M*2+2*I-1
      KK2=KK1+1
      LP=LP+1
      KP=KP+1
C
C
      IELMN(KK1,1)=LP
      IELMN(KK1,2)=LP+M+1
      IELMN(KK1,3)=LP+1

      IELMN(KK2,1)=KP
      IELMN(KK2,2)=KP+M
      IELMN(KK2,3)=KP+M+1

 10   CONTINUE

      WRITE(6,200) (I,(IELMN(I,J),J=1,3),I=1,NEL)
 200  FORMAT("CONNECTIVITY MATRIX",/,((I5,2X,I5,2X,I5,2X,I5)))
      RETURN
      END

C
C***********************************************************
C ASSEMBLES THE GLOBAL STIFFNESS MATRIX

      SUBROUTINE ASSEMB(IELMN,SLM,NEL,NGP2,IBAND,L,GSM)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION IELMN(NEL,3),SLM(6,6),GSM(NGP2,IBAND),KK(6)

      DO 10 INODE=1,3
      II=2*INODE
      KK(II)=2*IELMN(L,INODE)
      KK(II-1)=KK(II)-1
 10   CONTINUE

      DO 30 I=1,6
      K=KK(I)
      DO 30 J=1,6
      IF(KK(J).LT.K) GO TO 30
      LM=KK(J)-K+1
      GSM(K,LM)=GSM(K,LM)+SLM(I,J)
 30   CONTINUE

      RETURN
      END
C
C***********************************************************
C COMPUTES THE B ELEMENT MATRIX

      SUBROUTINE BETA(L,CORD,IELMN,NGP,NEL,DA,B)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION CORD(NGP,2),IELMN(NEL,3),B(3,6),X(3),Y(3)

      DO 3 I=1,3

      MS=IELMN(L,I)

      X(I)=CORD(MS,1)

 3    Y(I)=CORD(MS,2)

      DA=X(1)*Y(2)-X(1)*Y(3)+X(2)*Y(3)-X(2)*Y(1)+X(3)*Y(1)-X(3)*Y(2)

      DO 4 I=1,3

      DO 4 J=1,6

 4    B(I,J)=0.0

      B(1,1)=(Y(2)-Y(3))/DA

      B(1,3)=(Y(3)-Y(1))/DA


      B(1,5)=(Y(1)-Y(2))/DA

      B(2,2)=(X(3)-X(2))/DA

      B(2,4)=(X(1)-X(3))/DA

      B(2,6)=(X(2)-X(1))/DA

      DO 5 I=1,5,2

 5    B(3,I)=B(2,I+1)

      DO 6 I=2,6,2

 6    B(3,I)=B(1,I-1)

      RETURN
      END
C
C*************************************************************
C MULTIPLICATION OF TWO MATRICES OF THE FORM S(M4,L4)*Q(L4,N4)

      SUBROUTINE MULT(S,Q,C,L4,M4,N4)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION S(M4,L4),C(M4,N4),Q(L4,N4)

      DO 10 I=1,M4
      DO 10 J=1,N4
      C(I,J)=0.0
      DO 20 KY=I,L4
 20   C(I,J)=C(I,J)+S(I,KY)*Q(KY,J)
 10   CONTINUE

 90   RETURN
      END
C
C**********************************************************
C COMPUTATION OF ELASTIC MATRIX...D...
      SUBROUTINE ELASTI (EY,V,PISS,D)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION D(3,3)

      IF(PISS.EQ.1) GO TO 1

      DD=EY/(1.0-V**2)

      DOF=V*DD

      D3=EY/(2*(1.0+V))

      GO TO 2

 1    DD=(EY*(1.0-V))/((1.0+V)*(1.0-2.0*V))

      DOF=V*DD/(1.0-V)

      D3=EY/(2.0*(1.0+V))

 2    DO 3 I=1,2

      DO 3 J=1,2

      IF(I.EQ.J) GO TO 4

      D(I,J)=DOF

      GO TO 3

 4    D(I,J)=DD

 3    CONTINUE

      DO 5 I=1,2

      D(I,3)=0.0

 5    D(3,I)=0.0

      D(3,3)=D3
      RETURN
      END
C
C************************************************************
C IMPOSING BC---UNSCRAMBLING THE SYSTEM OF EQNS
C234567
      SUBROUTINE BOUNDA (M22,NGP2,IBAND,IGG,GSM,F)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION IGG(M22),GSM(NGP2,IBAND),F(NGP2)
C
      DO 20 I=1,M22
      KM=IGG(I)
      F(KM)=0.0
      GSM(KM,1)=1.0
C
      DO 20 J=2,IBAND
      KMJ=KM-J+1
      IF(KMJ.LE.0) GO TO 21
      F(KMJ)=F(KMJ)-GSM(KMJ,J)*F(KM)
      GSM(KMJ,J)=0.0
C
 21   KMJ=KM+J-1
      IF(KMJ.GT.NGP2) GO TO 20
      F(KMJ)=F(KMJ)-GSM(KM,J)*F(KM)
      GSM(KM,J)=0.0
 20   CONTINUE
C
      RETURN
      END

C
C**************************************************************
C234567
      SUBROUTINE HALLEY(KKK,AK,Q,MDIM,NDIM)
      IMPLICIT REAL*8(A-H,O-Z)
C  SYMMETRIC BANDED MATRIX EQUATION SOLVER
C
C  KKK=1 TRIANGULARIZES THE BANDED SYMMETRIC STIFFNESS MATRIX AK(MDIM,NDIM)
C  KKK=2 SOLVES FOR RIGHT HAND SIDE Q(MDIM), SOLUTION RETURNS IN Q(MDIM)
C
      DIMENSION AK(MDIM,NDIM),Q(MDIM)
      NER=MDIM
      IBAND=NDIM
      NRS=NER-1
      NR=NER
      IF (KKK.EQ.2) GO TO 200
      DO 120 N=1,NRS
      M=N-1
      MR=MIN0(IBAND,NR-M)
      PIVOT=AK(N,1)
      DO 120 L=2,MR
      CP=AK(N,L)/PIVOT
      I=M+L
      J=0
      DO 110 K=L,MR
      J=J+1
 110  AK(I,J)=AK(I,J)-CP*AK(N,K)
 120  AK(N,L)=CP
      GO TO 400
 200  DO 220 N=1,NRS
      M=N-1
      MR=MIN0(IBAND,NR-M)
      CP=Q(N)
      Q(N)=CP/AK(N,1)
      DO 220 L=2,MR
      I=M+L
 220  Q(I)=Q(I)-AK(N,L)*CP
      Q(NR)=Q(NR)/AK(NR,1)
      DO 320 I=1,NRS
      N=NR-I
      M=N-1
      MR=MIN0(IBAND,NR-M)
      DO 320 K=2,MR
      L=M+K
C
C  STORE COMPUTED DISPLACEMENTS IN LOAD VECTOR Q
C234567
 320  Q(N)=Q(N)-AK(N,K)*Q(L)
 400  RETURN
      END







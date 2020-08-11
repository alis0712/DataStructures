call station (im2,z,w)call station (im2,z,w)call station (im2,z,w)c234567
c A finite element code for solving plane elasticity 
c Piss=1 Solves Plane Strain Problem
c Piss Non Equal to 1 solves the plane stress problem

c234567
      program project2  
      implicit real*8(a-h,o-z)
      dimension ielmn(400,4),slm(8,8),gsm(902,26),kk(8),cord(451,2)
      dimension b(3,8),b1(3,8),bt(8,3),d(3,3),igg(22),f(902),strain(3,1)
      dimension uel(8,1),stress(3,1),xq(4),yq(4),dj(2,2)
c      dimension slmsum(8,8)
   
      
      
c     Elastic Constants EY=Young Modulus, v=Poisson's Ratio, D=Elasic Matrix

      piss=11.0
      if(piss.eq.1)go to 6
      write(6,99)
      width=1.0
      go to 7
 6    write(6,98)
      width=1.0
 7    ey=1.0
      v=0.30
      call elasti (ey,v,piss,d)
      write(6,100) ((d(i,j),j=1,3),i=1,3)

c     dada----geometry of the body
c     xl------length of the body
c     yl------height of the body
c     ngp-----# of grid points:::nel=# of elements
c     iband-----bandwidth
c     h-----displacement boundary length
c     qp-----applied traction in the y-direction
c
c
c      pi=datan(1.0d0)*4.0d0
c
c
c234567
      xl=10.0
      yl=1.0
      h=yl
      qp=-1.0
      n=40
      m=10

      dx=xl/n
      dy=yl/m
      xii=0.25
      n1=n+1
      m1=m+1
      m22=m1*2
      ngp=n1*m1
      ngp2=ngp*2
      iband=(m1+2)*2
      nel=m*n
      
c Matrix Description
c cord(ngp,2)----coordinate's matrix
c ielmn(nel,3)----associates each element with its nodes
c b1=d*b(3,6)
c bt(6,3)----transpose of b1
c slm(6,6)----element stiffness matrix in global sense
c gsm(ngp2,iband)----global stiffness matrix
c f(ngp2)-----global force vector

c234567
      do 8 i=1,ngp2
      do 8 j=1,iband
 8    gsm(i,j)=0.0
      call inodes(m,n,m1,nel,ielmn)
      call crdixy(m1,n1,ngp,dx,dy,cord)
      do 40 l=1,nel
c      slmsum(is,js)=0.0d0
      do 40  im=1,4
c      call localuxy(l,ielmn,f,nel,ngp2,ulocal)   
      call station (im,z,w)
      call beta(l,cord,ielmn,z,w,ngp,nel,b,da)
      call elasti (ey,v,piss,d)
      call mult(d,b,b1,3,3,8)
      do 41 i=1,3
      do 41 j=1,8
 41   bt(j,i)=b(i,j)
      call mult(bt,b1,slm,3,8,8)
      do 43 is=1,8
      do 43 js=1,8
c      slmsum(is,js)=0.0d0
c      do 42 ls=1,3
c      do 42 ms=1,8 
c       do iss=1,8
c       do jss=1,8
      
 43    slm(is,js)=slm(is,js)*da*width
c      slmsum(is,js)=0.0d0
c      slmsum(is,js)=slmsum(is,js)+slm(is,js)*da*width
c      call assemb(ielmn,slm,nel,ngp2,iband,l,gsm)
c      enddo
c      enddo
      call assemb(ielmn,slm,nel,ngp2,iband,l,gsm)    
 40   continue
c      call assemb(ielmn,slm,nel,ngp2,iband,l,gsm)
 
c      call  assemb(ielmn,slm,nel,ngp2,iband,l,gsm)
c      write(6,120)z,w,determ
c 120  format(3(f8.3,2x))
c      write(6,121)((B(i,j),j=1,8),i=1,3)
c 121  format(/,8(f8.4,1x))
      
      
c
      

c Apply Geometric BCs

      do 50 i=1,ngp2
 50   f(i)=0.0
      ngp3=ngp-m1
      do 60 i=m1,ngp3,m1
      f(2*i-1)=f(2*i-1)+0.0
      
      f(2*i)=f(2*i)+qp*xii/2.0
      f(2*(i+m1)-1)=f(2*(i+m1)-1)+0.0
      f((2*ngp)-(2*m))=-(3*qp*xl)/8
 60   f(2*(i+m1))=f(2*(i+m1))+qp*xii/2.0
      do 70 i=1,m1
      sof=(i-1)*dy+h
      if(sof.lt.yl) go to 70
      igg(2*i-1)=2*i-1
      igg(2*i)=2*i
 70   continue
      write(6,101)
      write(6,102)(i,i=1,m1)
      write(6,103)
      write(6,104)
      do 80 kx=1,4
      write(6,105)(((i-1)*m1+11),i=((kx-1)*10+1),kx*10)
 80   write(6,106)(f(((i-1)*m1+11)*2),i=((kx-1)*10+1),kx*10)
      i=451
      write(6,107) i,f(i*2)
      
      call bounda (m22,ngp2,iband,igg,gsm,f)
      
c Solve for nodal displacements 



      
       call halley (1,gsm,f,ngp2,iband)
       call halley (2,gsm,f,ngp2,iband)
       write(6,111)
       write(6,112)(i,f(2*i-1),f(2*i),i=1,ngp)
      
c calculation of the stress field stress=strain *d

      write(6,113)
      do 200 i=1,nel
      do 200 im2=1,4
      do 199 j=1,4
      jpn=ielmn(i,j)
      uel(2*j-1,1)=f(2*jpn-1)
 199  uel(2*j,1)=f(2*jpn)
      call station (im2,z,w)
      call beta (i,cord,ielmn,z,w,ngp,nel,b,da)
      call elasti (ey,v,piss,d)
      call mult (b,uel,strain,8,3,1)
      call mult (d,strain,stress,3,3,1)
      write(6,114)i,(stress(it,1),it=1,3)
 200  continue
 
      write(6,115)
c234567 
 98   format(//,10x,'Plain Strain case')

 99   format(//,10x,'Plain Stress case')

 100  format(//,10x,'Elastic matrix D',/(35x,3(f10.2,2x)))

 101  format(5(/),10x,'Displacement Boundary Conditions')

 102  format(//,4x,'node',11(4x,i2,4x))

 103  format(/,10x,11(2x,'ux=0.0',2x)/10x,11(2x,'uy=0.0',2x))

 104  format(5(/),10x,'Traction BC')

 105  format(//,4x,'node',10(4x,i3,4x))

 106  format(/,10x,10(2x,'fx=0.0',3x)/10x,10(2x,'fy=',f5.2,1x))

 107  format(//,4x,'node',4x,i3,//,12x,'fx=0.0'/12x,'fy=',f5.2)

 111  format(///,47x,'d',2x,'i',2x,'s',2x,'p',2x,'l',2x,'a',2x,'c',
    
     *2x,'e',2x,'m',2x,'e',2x,'n',2x,'t',2x,'s',/,40x,50('.'),5(/),
    
     :28x,76('*'),/,28x,2('*',6x,'*',2(14x,'*')),/,28x,2('*',1x,'node',
   
     *1x,'*',6x,'ux',6x,'*',6x,'uy',
    
     *6x,'*'),/,28x,2('*',6x,'*',2(14x,'*')),/,28x,76('*'))

 112  format((28x,2('*',1x,i4,1x,'*',2(1x,f12.4,1x,'*'))))

 113  format(28x,76('*'),6(/),55x,'s',2x,'t',2x,'r',2x,'e',2x,'s',2x,
     *'s',2x,'e',2x,'s',/,50x,32('.'),5(/),35x,61('*'),/,35x,'*',4(14x,
     *'*'),/,35x,'*',
     *4x,'element',3x,'*',6x,'sx',6x,'*',6x,'sy',6x,'*',6x,'sxy',5x,'*',
     */,35x,'*',4(14x,'*'),/,35x,61('*'))
 
 114  format((35x,'*',5x,i4,5x,'*',3(1x,f12.4,1x,'*')))
 115  format(35x,61('*'))

      stop
      end
c
c*****************************************************
c
      subroutine crdixy(m1,n1,ngp,dx,dy,cord)
      implicit real*8(a-h,o-z)
      dimension cord(ngp,2)
c
      do 1 i=1,m1
      do 1 j=1,n1

      jp=(j-1)*m1+i
      cord(jp,1)=(j-1)*dx
      cord(jp,2)=(i-1)*dy
 1    continue

c      do k=1,n
c      cord(2,1)=cord(2,1)-dx
c      cord(2,2)=-cord(2,1)
c      enddo
c
c
      write(6,100)(i,(cord(i,j),j=1,2),i=1,ngp)
 100  format("Coordinate Matrix",/,((i5,2x,f12.5,f12.5)))
c
c     
      return
      end
c
c*****************************************************
c
      subroutine inodes(m,n,m1,nel,ielmn)
      implicit real*8(a-h,o-z)
      dimension ielmn(nel,4)
      

      do 10  i=1,n
      do 10  j=1,m
      kl=m*(i-1)+j
      kn1=(i-1)*m1+j
      kn2=kn1+m1
      kn3=kn2+1
      kn4=kn1+1

      ielmn(kl,1)=kn1
      ielmn(kl,2)=kn2
      ielmn(kl,3)=kn3
      ielmn(kl,4)=kn4
     
 10   continue
      write(6,200) (i,(ielmn(i,j),j=1,4),i=1,nel)
 200  format("Connectivity Matrix",/,((i5,2x,i5,2x,i5,2x,i5,2x,i5)))
      return
      end
      
c
c***********************************************************
c Assembles the global stiffness matrix
      
      subroutine assemb(ielmn,slm,nel,ngp2,iband,l,gsm)
      implicit real*8(a-h,o-z)
      dimension ielmn(nel,4),slm(8,8),gsm(ngp2,iband),kk(8)

      do 10 inode=1,4
         ii=2*inode
         kk(ii)=2*ielmn(l,inode)
         kk(ii-1)=kk(ii)-1
 10      continue

         do 30 i=1,8
         k=kk(i)
         do 30 j=1,8
         if(kk(j).lt.k) go to 30
         lm=kk(j)-k+1
         gsm(k,lm)=gsm(k,lm)+slm(i,j)
 30      continue

         return 
         end
c
c***********************************************************
c computes the b element matrix
c234567      
      subroutine beta(l,cord,ielmn,z,w,ngp,nel,b,da)
      implicit real*8(a-h,o-z)
      dimension cord(ngp,2),ielmn(nel,4),b(3,8),xq(4),yq(4),dj(2,2)

      do 1 i=1,4

      ms=ielmn(l,i)

      xq(i)=cord(ms,1)

 1    yq(i)=cord(ms,2)

      d11=((w-1.0d0)*(xq(1)-xq(2))+(w+1.0d0)*(xq(3)-xq(4)))/4.0
     
      d12=((w-1.0d0)*(yq(1)-yq(2))+(w+1.0d0)*(yq(3)-yq(4)))/4.0
      
      d21=((z-1.0d0)*(xq(1)-xq(4))+(z+1.0d0)*(xq(3)-xq(2)))/4.0
      
      d22=((z-1.0d0)*(yq(1)-yq(4))+(z+1.0d0)*(yq(3)-yq(2)))/4.0
      
      da=d11*d22-d12*d21

      dj(1,1)=d22/da
      dj(1,2)=-d12/da
      dj(2,1)=-d21/da
      dj(2,2)=d11/da

      do 2 ks=1,2

      do 2 kl=1,8

 2    b(ks,kl)=0.0

      b(1,1)=(dj(1,1)*(w-1.0d0)+dj(1,2)*(z-1.0d0))/4.0
      
      b(2,2)=(dj(2,1)*(w-1.0d0)+dj(2,2)*(z-1.0d0))/4.0

      b(1,3)=-(dj(1,1)*(w-1.0d0)+dj(1,2)*(z+1.0d0))/4.0
      
      b(2,4)=-(dj(2,1)*(w-1.0d0)+dj(2,2)*(z+1.0d0))/4.0
      
      b(1,5)=(dj(1,1)*(w+1.0d0)+dj(1,2)*(z+1.0d0))/4.0

      b(2,6)=(dj(2,1)*(w+1.0d0)+dj(2,2)*(z+1.0d0))/4.0

      b(1,7)=-(dj(1,1)*(w+1.0d0)+dj(1,2)*(z-1.0d0))/4.0

      b(2,8)=-(dj(2,1)*(w+1.0d0)+dj(2,2)*(z-1.0d0))/4.0

      do 3 ls=1,7,2

      b(3,ls)=b(2,ls+1)
 3    b(3,ls+1)=b(1,ls)
      
c      write(6,200)(xq(i),yq(i),i=1,4)
c 200  format(2(f10.3,2x))
c      write(6,201)z,w,determ
c 201  format(3(f8.3,2x))
      return
      end
c
c
c************************************************************
c subroutine station chooses the values of z and w to be used
c In Gauss Integration for each integration station
c234567
      subroutine station (ms,z,w)
      implicit real*8(a-h,o-z)
c
      cs1=1.0/sqrt(3.0)
      if (ms-2)1,2,3
 1    z=cs1
      w=z
      go to 5
 2    z=-cs1
      w=-z
      go to 5
 3    if(ms.gt.3) go to 4
      z=-cs1
      w=z
      go to 5
 4    z=cs1
      w=-z
c
 5    return
      end
c*************************************************************
c Multiplication of two matrices of the form s(m4,l4)*q(l4,n4)

      subroutine mult(s,q,c,l4,m4,n4)
      implicit real*8(a-h,o-z)
      dimension s(m4,l4),c(m4,n4),q(l4,n4)

      do 10 i=1,m4
      do 10 j=1,n4
      c(i,j)=0.0
      do 20 ky=1,l4
 20   c(i,j)=c(i,j)+s(i,ky)*q(ky,j)
 10   continue

 90   return
      end
c
c**********************************************************
c computation of elastic matrix...d...
      subroutine elasti (ey,v,piss,d)
      implicit real*8(a-h,o-z)
      dimension d(3,3)

      if(piss.eq.1) go to 1

      dd=ey/(1.0-v**2)

      dof=v*dd

      d3=ey/(2*(1.0+v))

      go to 2

 1    dd=(ey*(1.0-v))/((1.0+v)*(1.0-2.0*v))
 
      dof=v*dd/(1.0-v)
 
      d3=ey/(2.0*(1.0+v))

 2    do 3 i=1,2

      do 3 j=1,2

      if(i.eq.j) go to 4

      d(i,j)=dof

      go to 3

 4    d(i,j)=dd

 3    continue

      do 5 i=1,2

      d(i,3)=0.0

 5    d(3,i)=0.0

      d(3,3)=d3
      return
      end
c
c************************************************************
c Imposing BC---Unscrambling the system of eqns
c234567
      subroutine bounda (m22,ngp2,iband,igg,gsm,f)
      implicit real*8(a-h,o-z)
      dimension igg(m22),gsm(ngp2,iband),f(ngp2)
c
      do 20 i=1,m22 
      km=igg(i)
      f(km)=0.0
      gsm(km,1)=1.0 
c
      do 20 j=2,iband
      kmj=km-j+1
      if(kmj.le.0) go to 21
      f(kmj)=f(kmj)-gsm(kmj,j)*f(km)
      gsm(kmj,j)=0.0
c
 21   kmj=km+j-1
      if(kmj.gt.ngp2) go to 20
      f(kmj)=f(kmj)-gsm(km,j)*f(km)
      gsm(km,j)=0.0 
 20   continue
c
      return
      end 

c
c**************************************************************
c234567
      subroutine halley(kkk,ak,q,mdim,ndim)
      implicit real*8(a-h,o-z)
c  symmetric banded matrix equation solver
c
c  kkk=1 triangularizes the banded symmetric stiffness matrix ak(mdim,ndim)
c  kkk=2 solves for right hand side q(mdim), solution returns in q(mdim)
c
      dimension ak(mdim,ndim),q(mdim)
      ner=mdim
      iband=ndim
      nrs=ner-1
      nr=ner
      if (kkk.eq.2) go to 200
      do 120 n=1,nrs
      m=n-1
      mr=min0(iband,nr-m)
      pivot=ak(n,1)
      do 120 l=2,mr
      cp=ak(n,l)/pivot
      i=m+l
      j=0
      do 110 k=l,mr
      j=j+1
 110  ak(i,j)=ak(i,j)-cp*ak(n,k)
 120  ak(n,l)=cp
      go to 400
 200  do 220 n=1,nrs
      m=n-1
      mr=min0(iband,nr-m)
      cp=q(n)
      q(n)=cp/ak(n,1)
      do 220 l=2,mr
      i=m+l
 220  q(i)=q(i)-ak(n,l)*cp
      q(nr)=q(nr)/ak(nr,1)
      do 320 i=1,nrs
      n=nr-i
      m=n-1
      mr=min0(iband,nr-m)
      do 320 k=2,mr
      l=m+k
c
c  store computed displacements in load vector q
c234567
 320  q(n)=q(n)-ak(n,k)*q(l)
 400  return
      end

c*************************************************************     

   


       

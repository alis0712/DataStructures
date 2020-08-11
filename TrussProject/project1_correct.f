c234567
      program project1
      implicit real*8(a-h,o-z)
      dimension gsm(164,164),slm(4,4),cord(82,2),ielmn(161,2)
      dimension elength(161),thetal(161),thetald(161)
      dimension gsmb(164,8),fn(164),igg(3)
      dimension ulocal(4),fnlocal(4),an(161),stress(161)
c
      area=1.0d0
      amodu=1.0d0
c    
c      node1=0
c      node2=0

      pi=datan(1.0d0)*4.0d0

c
      ell=2.50d0
      h=0.25d0

      x0=0.0d0
      y0=0.0d0
c
c     read(5,601) nucells4
c     601 format(i5)
c
      nucells4=5
      nucells2=2*nucells4
      nucells=2*nucells2
      n=2*nucells
      n1=n+1
      ngp=2*n1
      nel=4*n+1
      ngp2=2*ngp
      iband=8

c     call cordxy(cord,ngp,el1,el2,el3,h1,h2,h3,th1,th2)
c     call econ(ielmn,nel)
      dx=ell/dfloat(n)
      np1=(1.0d0/dx)*2+1
      np2=(1.25d0/dx)*2+1
      np3=(1.50d0/dx)*2+1
      np4=(2.00d0/dx)*2+2
      np5=(0.0d0/dx)*2+2
c
      write(6,*)np1,np2,np3,np4,np5

      call cordxyp(cord,ngp,x0,y0,ell,h,nucells)
      call econp(ielmn,nel,nucells)
c      call mesh2(ielmn,cord,nel,ngp)
c
       do i=1,ngp2
       do j=1,ngp2
       gsm(i,j)=0.0d0
       enddo
       fn(i)=0.0d0
       enddo
c
       do i=1,ngp2
       do j=1,iband
       gsmb(i,j)=0.0d0
       enddo
       enddo

       do i=1,4
       do j=1,4
       slm(i,j)=0.0d0
       enddo
       enddo
c
c     l=2*n+2

      call geometry(ielmn,cord,ngp,nel,elength,thetal,thetald)
c

      do l=1,nel
      alength=elength(l)
      theta=thetal(l)
c
c
      call klocal(area,alength,amodu,theta,slm)
      call assemb2(l,ngp2,ielmn,nel,slm,gsm)
      call assemb(ielmn,slm,nel,ngp2,iband,l,gsmb)
      enddo
c
      igg(1)=1
      igg(2)=2
c      igg(3)=2*(2*n+1)-1
c      igg(3)=0
      igg(3)=2*(2*n+1)
      m12=3
      write(7,400)(igg(i),i=1,m12)
 400  format("Constrained Degrees of Freedom",2x,4(i4,1x))
c
      
     
      fn(2*np1)=-0.5d0
      fn(2*np2)=-1.0d0
      fn(2*np3)=-0.5d0
      fn(2*np4)=-2.0d0
      fn(2*np5-1)=-1.5d0
cxc  
c
      write(7,300) (i,fn(2*i-1),fn(2*i),i=1,ngp)
 300    format("Node",1x,i3,1x,"F_x=",f10.6,2x,"F_y=",f10.6)
c
      call bounda(m12,ngp2,iband,igg,gsmb,fn)
c
      call halley(1,gsmb,fn,ngp2,iband)
      call halley(2,gsmb,fn,ngp2,iband)
c
         write(7,301)(i,fn(2*i-1),fn(2*i),i=1,ngp)
 301    format("Node",1x,i3,1x,"u_x=",f10.6,2x,"u_y=",f10.6)
c 301     format(1x,i3,1x,f10.6,2x,f10.6)
c
c     post processing
c
      do l=1,nel
      call localuxy(l,ielmn,fn,nel,ulocal,node1,node2)
      alength=elength(l)
      theta=thetal(l)
      call klocal(area,alength,amodu,theta,slm)
      call mult(fnlocal,slm,ulocal)
      an(l)=dsqrt(fnlocal(1)**2+fnlocal(2)**2)
      stress(l)=an(l)/area
      enddo

      write(7,501) 
 501  format(/,"El #",2x,"El length",2x,"El angle",2x,"El Axial Force"
     +,2x,"El Axial Stress",/)
      write(7,500)(i,elength(i),thetald(i),an(i),stress(i),i=1,nel)
 500  format((i3,4(f10.6,2x)))

      stop
      end
c
c*********************************************************
c
      subroutine cordxyp(cord,ngp,x0,y0,ell,h,nucells)
      implicit real*8(a-h,o-z)
      dimension cord(ngp,2)

      n=2*nucells
      n1=n+1
      dx=ell/dfloat(n)
c

c234567
      do i=1,n1
         cord(2*i-1,1)=(dfloat(i-1)*dx)+x0
         cord(2*i-1,2)=y0

         cord(2*i,1)=cord(2*i-1,1)
         cord(2*i,2)=y0+h
      enddo
c234567
      write(6,100)(i,(cord(i,j),j=1,2),i=1,ngp)
 100    format("Coordinate Matrix",/,((i5,2x,f12.5,2x,f12.5)))
      return
      end
c
c****************************
c
      subroutine econp(ielmn,nel,nucells)
      implicit real*8(a-h,o-z)
      dimension ielmn(nel,2)
c
      n=2*nucells
c234567

      do i=1,n
         ielmn(i,1)=2*i-1
         ielmn(i,2)=2*i+1
         ielmn(n+i,1)=2*i
         ielmn(n+i,2)=2*i+2
      enddo
c234567
      do j=1,nucells

         jp=4*(j-1)+1
         jp1=2*n+4*j
         ielmn(2*n+4*j-3,1)=jp
         ielmn(2*n+4*j-3,2)=jp+1
         ielmn(2*n+4*j-2,1)=jp
         ielmn(2*n+4*j-2,2)=jp+3
         ielmn(2*n+4*j-1,1)=jp+2
         ielmn(2*n+4*j-1,2)=jp+3
         ielmn(2*n+4*j,1)=jp+3
         ielmn(2*n+4*j,2)=jp+4
      enddo

      ielmn(nel,1)=2*(n+1)-1
      ielmn(nel,2)=2*(n+1)
c234567
      write(6,100)(l,(ielmn(l,j),j=1,2),l=1,nel)
 100    format("Connectivity Matrix",/,((i5,2x,i5,2x,i5)))

       return
       end
c
c******************************************
c
      subroutine klocal(area,alength,amodu,theta,slm)
      implicit real*8(a-h,o-z)
      dimension slm(4,4)
c
      pi=datan(1.0d0)*4.0d0
      q=theta
c     q=theta*pi/180.0d0

      factor=amodu*area/alength
      c=dcos(q)
      s=dsin(q)
c
      slm(1,1)=factor*c**2
      slm(1,2)=factor*c*s
      slm(1,3)=-factor*c**2
      slm(1,4)=-factor*c*s
c
      slm(2,2)=factor*s**2
      slm(2,3)=-factor*c*s
      slm(2,4)=-factor*s**2
c
      slm(3,3)=factor*c**2
      slm(3,4)=factor*c*s
c
      slm(4,4)=factor*s**2

      do i=2,4
      do j=1,i-1
      slm(i,j)=slm(j,i)
      enddo
      enddo
c
      write(6,101)
 101   format(/,"Local Stiffness Matrix",/)
      write(6,100)((slm(i,j),i=1,4),j=1,4)
 100   format(/,4(f12.5,2x))
c
      return
      end
c
c*************************************
c
      subroutine assemb2(l,ngp2,ielmn,nel,slm,gsm)
      implicit real*8(a-h,o-z)
      dimension slm(4,4),ielmn(nel,2),gsm(ngp2,ngp2),kk(4)
      do inode=1,2
      kk(2*inode)=ielmn(l,inode)*2
      kk(2*inode-1)=kk(2*inode)-1
      enddo
c
c
      do i=1,4
      do j=1,4
      k1=kk(i)
      k2=kk(j)
      gsm(k1,k2)=gsm(k1,k2)+slm(i,j)
      enddo
      enddo
c
c
c      write(6,101)
 101    format(/,"Square Stiffness Matrix",/)
c      write(6,100)((gsm(i,j),i=1,ngp2),j=1,ngp2)
 100    format(10(f7.4,1x))
c
c
      return
      end
c
c******************************************
c
      subroutine geometry(ielmn,cord,ngp,nel,elength,thetal,thetald)
      implicit real*8(a-h,o-z)
      dimension  ielmn(nel,2),cord(ngp,2),elength(nel),thetal(nel)
      dimension thetald(nel)
c
      pi=4.0d0*datan(1.0d0)
c
      do l=1,nel
      jp1=ielmn(l,1)
      jp2=ielmn(l,2)
c
      dx=cord(jp2,1)-cord(jp1,1)
      dy=cord(jp2,2)-cord(jp1,2)
c
      elength(l)=dsqrt(dx**2+dy**2)
      thetal(l)=datan(dy/dx)
      thetald(l)=thetal(l)*180.0d0/pi
      enddo
      write(6,101)
 101   format(/,"Element Connectivity, Element Length and Element Angle"
     +,/)
      write(6,100)(l,ielmn(l,1),ielmn(l,2),elength(l),thetal(l)
     +,thetald(l),l=1,nel)
 100   format((3(i5,1x),3(f12.5,2x)))
c
      return
      end
c
c
c
c
***********************************************************************
c
c  assembles the banded global stiffness matrix
c
      subroutine assemb(ielmn,slm,nel,ngp2,iband,l,gsmb)
      implicit real*8(a-h,o-z)
      dimension ielmn(nel,2),slm(4,4),gsmb(ngp2,iband),kk(4)
c
      do 10 inode=1,2
      ii=2*inode
      kk(ii)=2*ielmn(l,inode)
      kk(ii-1)=kk(ii)-1
 10    continue
c
      do 30 i=1,4
      k=kk(i)
      do 30 j=1,4
      if(kk(j).lt.k) go to 30
      lm=kk(j)-k+1
      gsmb(k,lm)=gsmb(k,lm)+slm(i,j)
 30    continue
c
c      write(6,201)
 201   format(/,"Local Stiffness Matrix",/)
c      write(6,200)((slm(i,j),i=1,4),j=1,4)
 200   format(/,4(f12.5,2x))
c
c
c      write(6,101)
 101   format(/,"Banded Stiffness Matrix",/)
c      write(6,100)((gsmb(i,j),j=1,iband),i=1,ngp2)
 100   format(8(f9.3,1x))
      return
      end
c
c
c
c******************************************************************
c
c  imposing boundary contitions--unscrambling the system of eqns
c
      subroutine bounda (m12,ngp2,iband,igg,gsmb,fn)
      implicit real*8(a-h,o-z)
      dimension igg(m12),gsmb(ngp2,iband),fn(ngp2)
c
      do 20 i=1,m12
      km=igg(i)
      fn(km)=0.0d0
      gsmb(km,1)=1.0d0
c
      do 20 j=2,iband
      kmj=km-j+1
      if(kmj.le.0) go to 21
      fn(kmj)=fn(kmj)-gsmb(kmj,j)*fn(km)
      gsmb(kmj,j)=0.0d0
c
 21    kmj=km+j-1
      if(kmj.gt.ngp2) go to 20
      fn(kmj)=fn(kmj)-gsmb(km,j)*fn(km)
      gsmb(km,j)=0.0d0
 20    continue
c
      write(6,301)
 301  format(/,"fn",/)
      write(6,300)((fn))
 300  format(/,f12.5,/)

      return
      end
c
c
c***************************************************************
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
 110   ak(i,j)=ak(i,j)-cp*ak(n,k)
 120    ak(n,l)=cp
      go to 400
 200   do 220 n=1,nrs
      m=n-1
      mr=min0(iband,nr-m)
      cp=q(n)
      q(n)=cp/ak(n,1)
      do 220 l=2,mr
      i=m+l
 220   q(i)=q(i)-ak(n,l)*cp
      q(nr)=q(nr)/ak(nr,1)
      do 320 i=1,nrs
      n=nr-i
      m=n-1
      mr=min0(iband,nr-m)
      do 320 k=2,mr
      l=m+k
c
c  store computed displacements in load vector q
c
 320   q(n)=q(n)-ak(n,k)*q(l)
 400   return
      end
c
c************************************************************
c234567
     
      subroutine localuxy(l,ielmn,fn,nel,ulocal,node1,node2)
      implicit real*8(a-h,o-z)
      dimension ulocal(4),ielmn(nel,2),fn(4)
c      do inode=1,2
c         fn(2*inode)=ielmn(l,inode)*2
c         fn(2*inode-1)=fn(2*inode)-1
c      enddo

     
        
       node1=ielmn(l,1)
       node2=ielmn(l,2)
      
       
       ulocal(1)=fn(((2*node1)-1))
       ulocal(2)=fn(((2*node1)))
       ulocal(3)=fn(((2*node2-1)))
       ulocal(4)=fn(((2*node2)))

       
      write(6,301)
 301  format(/,"L",/)
      write(6,300)((l))
 300  format(/,i5,/)

      write(6,201)
 201  format(/,"Node 1",/)
      write(6,200)((node1))
 200  format(/,i5,/)

      write(6,401)
 401   format(/,"Node 2",/)
      write(6,400)((node2))
 400   format(/,i5,/)
     
      write(6,101)

 101  format(/,"u Local",/)
      write(6,100)((ulocal(i)),i=1,4)
 100  format(/,4(f12.5,2x),/)
c   
      return
      end
c
c*************************************************************
c234567
      subroutine mult(fnlocal,slm,ulocal)
      implicit real*8(a-h,o-z)
      dimension fnlocal(4),ulocal(4),slm(4,4)
c
      do i=1,4
       fnlocal(i)=0.0*d0
      enddo
      
       do i=1,4
         do m=1,4
            fnlocal(i)=fnlocal(i)+(slm(i,m)*ulocal(m))
         enddo
       enddo

c      write(6,101)
c 101  format(/,"local force vectors",/)
      return
      end
c

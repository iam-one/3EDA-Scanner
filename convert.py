import numpy as np
import pyvista as pv

from config import POINTCLOUD_PATH, MESH_PATH

def genMesh():
    points = pv.wrap(np.genfromtxt(POINTCLOUD_PATH, delimiter=",", dtype=np.float32))
    recons = points.reconstruct_surface()

    recons.save(MESH_PATH)

    # pl = pv.Plotter(shape=(1, 2))
    # pl.add_mesh(points)
    # pl.add_title('Point Cloud of 3D Surface')
    # pl.subplot(0, 1)
    # pl.add_mesh(recons, color=True, show_edges=True)
    # pl.add_title('Reconstructed Surface')
    # pl.show()

if __name__ == "main":
    genMesh()
import numpy as np
import pyvista as pv

from config import POINTCLOUD_PATH, MESH_PATH

def genMesh():
    points = np.genfromtxt(POINTCLOUD_PATH, delimiter=",", dtype=np.float32)
    point_cloud = pv.PolyData(points)
    mesh = point_cloud.reconstruct_surface()
    mesh.save(MESH_PATH)

genMesh()